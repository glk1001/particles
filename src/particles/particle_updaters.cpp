module;

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>
#include <glm/vec4.hpp>

module Particles.ParticleUpdaters;

namespace PARTICLES::UPDATERS
{

EulerUpdater::EulerUpdater(const glm::vec4& globalAcceleration) noexcept
  : m_globalAcceleration{globalAcceleration}
{
}

auto EulerUpdater::Update(const double dt, ParticleData* const particleData) noexcept -> void
{
  const auto globalA = glm::vec4{dt * static_cast<double>(m_globalAcceleration.x),
                                 dt * static_cast<double>(m_globalAcceleration.y),
                                 dt * static_cast<double>(m_globalAcceleration.z),
                                 0.0};

  const auto localDT = static_cast<float>(dt);
  const auto endId   = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->IncAcceleration(i, globalA);
  }

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->IncVelocity(i, localDT * particleData->GetAcceleration(i));
  }

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->IncPosition(i, localDT * particleData->GetVelocity(i));
  }
}

FloorUpdater::FloorUpdater(const float floorY, const float bounceFactor) noexcept
  : m_floorY{floorY},
    m_bounceFactor{bounceFactor}
{
}

auto FloorUpdater::Update([[maybe_unused]] const double dt,
                          ParticleData* const particleData) noexcept -> void
{
  const auto endId = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    if (particleData->GetPosition(i).y < m_floorY)
    {
      auto force = glm::vec4{particleData->GetAcceleration(i)};
      if (const auto normalFactor = glm::dot(force, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
        normalFactor < 0.0F)
      {
        force -= glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * normalFactor;
      }

      const auto velFactor =
          glm::dot(particleData->GetVelocity(i), glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      //if (velFactor < 0.0)
      particleData->DecVelocity(
          i,
          glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * (1.0F + m_bounceFactor) * velFactor);

      particleData->SetAcceleration(i, force);
    }
  }
}

auto AttractorUpdater::Update([[maybe_unused]] const double dt,
                              ParticleData* const particleData) noexcept -> void
{
  const auto endId = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    const auto particlePosition = particleData->GetPosition(i);
    for (const auto& attractorPosition : m_attractorPositions)
    {
      const auto offset = glm::vec4{attractorPosition.x - particlePosition.x,
                                    attractorPosition.y - particlePosition.y,
                                    attractorPosition.z - particlePosition.z,
                                    0.0F};
      const auto distSq = glm::dot(offset, offset);
      const auto force  = attractorPosition.w / distSq;

      particleData->IncAcceleration(i, offset * force);
    }
  }
}

auto BasicColorUpdater::Update([[maybe_unused]] const double dt,
                               ParticleData* const particleData) noexcept -> void
{
  const auto endId = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->SetColor(i,
                           glm::mix(particleData->GetStartColor(i),
                                    particleData->GetEndColor(i),
                                    particleData->GetTime(i).z));
  }
}

PositionColorUpdater::PositionColorUpdater(const glm::vec4& minPosition,
                                           const glm::vec4& maxPosition) noexcept
  : m_minPosition{minPosition},
    m_maxPosition{maxPosition}
{
}

namespace
{

[[nodiscard]] inline auto GetScaledValues(const glm::vec4& values,
                                          const glm::vec4& minValues,
                                          const glm::vec4& diffsMinMax) noexcept -> glm::vec4
{
  static constexpr auto VEC3_LEN = 3;
  auto scaledVales               = glm::vec4{};

  for (auto i = 0; i < VEC3_LEN; ++i)
  {
    auto value = values[i];
    if (value < minValues[i])
    {
      value = -value;
    }

    scaledVales[i] = (value - minValues[i]) / diffsMinMax[i];
  }

  return scaledVales;
}

} // namespace

auto PositionColorUpdater::Update([[maybe_unused]] const double dt,
                                  ParticleData* const particleData) noexcept -> void
{
  const auto endId = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    const auto scaledPositions =
        GetScaledValues(particleData->GetPosition(i), m_minPosition, m_diffMinMaxPosition);

    particleData->SetColor(
        i,
        {scaledPositions
         .r, // glm::mix(particleData->m_startCol[i].r, particleData->m_endCol[i].r, scaler);
         scaledPositions
         .g, // glm::mix(particleData->m_startCol[i].g, particleData->m_endCol[i].g, scaleg);
         scaledPositions
         .b, // glm::mix(particleData->m_startCol[i].b, particleData->m_endCol[i].b, scaleb);
         glm::mix(particleData->GetStartColor(i).a,
                  particleData->GetEndColor(i).a,
                  particleData->GetTime(i).z)});
  }
}

VelocityColorUpdater::VelocityColorUpdater(const glm::vec4& minVelocity,
                                           const glm::vec4& maxVelocity) noexcept
  : m_minVelocity{minVelocity},
    m_maxVelocity{maxVelocity}
{
}

auto VelocityColorUpdater::Update([[maybe_unused]] const double dt,
                                  ParticleData* const particleData) noexcept -> void
{
  const auto endId = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    const auto scaledVelocities =
        GetScaledValues(particleData->GetPosition(i), m_minVelocity, m_diffMinMaxVelocity);
    particleData->SetColor(i,
                           {glm::mix(m_tintColor.r, scaledVelocities.r, m_mixAmount),
                            glm::mix(m_tintColor.g, scaledVelocities.g, m_mixAmount),
                            glm::mix(m_tintColor.b, scaledVelocities.b, m_mixAmount),
                            glm::mix(particleData->GetStartColor(i).a,
                                     particleData->GetEndColor(i).a,
                                     particleData->GetTime(i).z)});

    /**
    particleData->SetColor(
        i,
        {glm::mix(
             m_tintColor.r,
             glm::mix(particleData->GetStartColor(i).r, particleData->GetEndColor(i).r, scaleR),
             particleData->GetTime(i).z),
         glm::mix(
             m_tintColor.g,
             glm::mix(particleData->GetStartColor(i).g, particleData->GetEndColor(i).g, scaleG),
             particleData->GetTime(i).z),
         glm::mix(
             m_tintColor.b,
             glm::mix(particleData->GetStartColor(i).b, particleData->GetEndColor(i).b, scaleB),
             particleData->GetTime(i).z),
         glm::mix(particleData->GetStartColor(i).a,
                  particleData->GetEndColor(i).a,
                  particleData->GetTime(i).z)});
  **/
  }
}

auto BasicTimeUpdater::Update(const double dt, ParticleData* const particleData) noexcept -> void
{
  auto endId = particleData->GetAliveCount();

  if (0 == endId)
  {
    return;
  }

  const auto localDT = static_cast<float>(dt);

  for (auto i = 0U; i < endId; ++i)
  {
    const auto newXTime = particleData->GetTime(i).x - localDT;

    // Interpolation: From 0 (start of life) till 1 (end of life)
    const auto newZTime =
        1.0F - (particleData->GetTime(i).x * particleData->GetTime(i).w); // .w is 1.0/max lifetime

    particleData->SetTime(
        i,
        {newXTime, particleData->GetTime(i).y, newZTime, particleData->GetTime(i).w});

    if (newXTime < 0.0F)
    {
      particleData->Kill(i);
      endId = particleData->GetAliveCount() < particleData->GetCount()
                ? particleData->GetAliveCount()
                : particleData->GetCount();
    }
  }
}

} // namespace PARTICLES::UPDATERS
