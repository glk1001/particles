module;

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>
#include <glm/vec4.hpp>

module Particles.ParticleUpdaters;

import Particles.Particles;

namespace PARTICLES::UPDATERS
{

// NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)

namespace
{

[[nodiscard]] auto GetBasicAlpha(const size_t i, const ParticleData& particleData)
{
  return glm::mix(
      particleData.GetStartColor(i).a, particleData.GetEndColor(i).a, particleData.GetTime(i).z);
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
[[nodiscard]] auto GetScaledValues(const glm::vec4& values,
                                   const glm::vec4& minValues,
                                   const glm::vec4& diffsMinMax) noexcept -> glm::vec4
{
  static constexpr auto VEC3_LEN = 3;

  auto scaledVales = glm::vec4{};

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

EulerUpdater::EulerUpdater(const glm::vec4& globalAcceleration) noexcept
  : m_globalAcceleration{globalAcceleration}
{
}

auto EulerUpdater::Update(const double dt, ParticleData& particleData) noexcept -> void
{
  const auto globalAcceleration = glm::vec4{dt * static_cast<double>(m_globalAcceleration.x),
                                            dt * static_cast<double>(m_globalAcceleration.y),
                                            dt * static_cast<double>(m_globalAcceleration.z),
                                            0.0};
  const auto localDt            = static_cast<float>(dt);
  const auto numAlive           = particleData.GetAliveCount();

  for (auto i = 0U; i < numAlive; ++i)
  {
    particleData.IncAcceleration(i, globalAcceleration);
  }

  for (auto i = 0U; i < numAlive; ++i)
  {
    particleData.IncVelocity(i, localDt * particleData.GetAcceleration(i));
  }

  for (auto i = 0U; i < numAlive; ++i)
  {
    particleData.IncPosition(i, localDt * particleData.GetVelocity(i));
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
FloorUpdater::FloorUpdater(const float floorY, const float bounceFactor) noexcept
  : m_floorY{floorY}, m_bounceFactor{bounceFactor}
{
}

auto FloorUpdater::Update([[maybe_unused]] const double dt,
                          ParticleData& particleData) noexcept -> void
{
  const auto numAlive = particleData.GetAliveCount();

  for (auto i = 0U; i < numAlive; ++i)
  {
    if (particleData.GetPosition(i).y >= m_floorY)
    {
      continue;
    }

    auto force = glm::vec4{particleData.GetAcceleration(i)};
    if (const auto normalFactor = glm::dot(force, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
        normalFactor < 0.0F)
    {
      force -= glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * normalFactor;
    }

    const auto velFactor = glm::dot(particleData.GetVelocity(i), glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
    //if (velFactor < 0.0)
    particleData.DecVelocity(
        i, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * (1.0F + m_bounceFactor) * velFactor);

    particleData.SetAcceleration(i, force);
  }
}

auto AttractorUpdater::Update([[maybe_unused]] const double dt,
                              ParticleData& particleData) noexcept -> void
{
  const auto numAlive = particleData.GetAliveCount();

  for (auto i = 0U; i < numAlive; ++i)
  {
    const auto particlePosition = particleData.GetPosition(i);
    for (const auto& attractorPosition : m_attractorPositions)
    {
      const auto offset = glm::vec4{attractorPosition.x - particlePosition.x,
                                    attractorPosition.y - particlePosition.y,
                                    attractorPosition.z - particlePosition.z,
                                    0.0F};
      const auto distSq = glm::dot(offset, offset);
      const auto force  = attractorPosition.w / distSq;

      particleData.IncAcceleration(i, offset * force);
    }
  }
}

auto BasicColorUpdater::Update([[maybe_unused]] const double dt,
                               ParticleData& particleData) noexcept -> void
{
  const auto& mixedTintColor = GetMixedTintColor();
  const auto numAlive        = particleData.GetAliveCount();

  for (auto i = 0U; i < numAlive; ++i)
  {
    const auto basicColor = glm::mix(
        particleData.GetStartColor(i), particleData.GetEndColor(i), particleData.GetTime(i).z);

    particleData.SetColor(i,
                          {basicColor.r * mixedTintColor.r,
                           basicColor.g * mixedTintColor.g,
                           basicColor.b * mixedTintColor.b,
                           basicColor.a});
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
PositionColorUpdater::PositionColorUpdater(const glm::vec4& minPosition,
                                           const glm::vec4& maxPosition) noexcept
  : m_minPosition{minPosition}, m_maxPosition{maxPosition}
{
}

auto PositionColorUpdater::Update([[maybe_unused]] const double dt,
                                  ParticleData& particleData) noexcept -> void
{
  const auto& mixedTintColor = GetMixedTintColor();
  const auto numAlive        = particleData.GetAliveCount();

  for (auto i = 0U; i < numAlive; ++i)
  {
    const auto scaledPosition =
        GetScaledValues(particleData.GetPosition(i), m_minPosition, m_diffMinMaxPosition);

    particleData.SetColor(i,
                          {scaledPosition.r * mixedTintColor.r,
                           scaledPosition.g * mixedTintColor.g,
                           scaledPosition.b * mixedTintColor.b,
                           GetBasicAlpha(i, particleData)});
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
VelocityColorUpdater::VelocityColorUpdater(const glm::vec4& minVelocity,
                                           const glm::vec4& maxVelocity) noexcept
  : m_minVelocity{minVelocity}, m_maxVelocity{maxVelocity}
{
}

auto VelocityColorUpdater::Update([[maybe_unused]] const double dt,
                                  ParticleData& particleData) noexcept -> void
{
  const auto& mixedTintColor = GetMixedTintColor();
  const auto numAlive        = particleData.GetAliveCount();

  for (auto i = 0U; i < numAlive; ++i)
  {
    const auto scaledVelocity =
        GetScaledValues(particleData.GetPosition(i), m_minVelocity, m_diffMinMaxVelocity);

    particleData.SetColor(i,
                          {scaledVelocity.r * mixedTintColor.r,
                           scaledVelocity.g * mixedTintColor.g,
                           scaledVelocity.b * mixedTintColor.b,
                           GetBasicAlpha(i, particleData)});
  }
}

auto BasicTimeUpdater::Update(const double dt, ParticleData& particleData) noexcept -> void
{
  auto numAlive = particleData.GetAliveCount();

  if (0 == numAlive)
  {
    return;
  }

  const auto localDt = static_cast<float>(dt);

  auto i = 0U;
  while (i < numAlive)
  {
    const auto newXTime = particleData.GetTime(i).x - localDt;

    // Interpolation: From 0 (start of life) till 1 (end of life)
    const auto newZTime =
        1.0F - (particleData.GetTime(i).x * particleData.GetTime(i).w); // .w is 1.0/max lifetime

    particleData.SetTime(
        i, {newXTime, particleData.GetTime(i).y, newZTime, particleData.GetTime(i).w});

    if (newXTime < 0.0F)
    {
      particleData.Kill(i);
      numAlive = particleData.GetAliveCount() < particleData.GetCount()
                     ? particleData.GetAliveCount()
                     : particleData.GetCount();
    }

    ++i;
  }
}

// NOLINTEND(cppcoreguidelines-pro-type-union-access)

} // namespace PARTICLES::UPDATERS
