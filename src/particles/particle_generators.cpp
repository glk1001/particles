module;

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>
#include <glm/vec4.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846 /* pi */
#endif

module Particles.ParticleGenerators;

namespace PARTICLES::GENERATORS
{

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
BoxPositionGenerator::BoxPositionGenerator(const glm::vec4& position,
                                           const glm::vec4& maxStartPositionOffset) noexcept
  : m_position{position}, m_maxStartPositionOffset{maxStartPositionOffset}
{
}

// NOLINTBEGIN(bugprone-easily-swappable-parameters,
//             cppcoreguidelines-pro-type-union-access)
auto BoxPositionGenerator::Generate([[maybe_unused]] const double dt,
                                    ParticleData* const particleData,
                                    const size_t startId,
                                    const size_t endId) noexcept -> void
{
  const auto posMin = glm::vec4{m_position.x - m_maxStartPositionOffset.x,
                                m_position.y - m_maxStartPositionOffset.y,
                                m_position.z - m_maxStartPositionOffset.z,
                                1.0};
  const auto posMax = glm::vec4{m_position.x + m_maxStartPositionOffset.x,
                                m_position.y + m_maxStartPositionOffset.y,
                                m_position.z + m_maxStartPositionOffset.z,
                                1.0};

  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetPosition(i, glm::linearRand(posMin, posMax));
  }
}
// NOLINTEND

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
RoundPositionGenerator::RoundPositionGenerator(const glm::vec4& center,
                                               const double xRadius,
                                               const double yRadius) noexcept
  : m_center{center}, m_xRadius{static_cast<float>(xRadius)}, m_yRadius{static_cast<float>(yRadius)}
{
}

auto RoundPositionGenerator::Generate([[maybe_unused]] const double dt,
                                      ParticleData* const particleData,
                                      // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
                                      const size_t startId,
                                      const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    // TODO(glk) - Need '2.01' instead of '2.0' to cover small radial gap (see tunnel effect).
    const auto ang = glm::linearRand(0.0, M_PI * 2.01);
    particleData->SetPosition(i,
                              m_center + glm::vec4(static_cast<double>(m_xRadius) * std::sin(ang),
                                                   static_cast<double>(m_yRadius) * std::cos(ang),
                                                   0.0,
                                                   1.0));
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
BasicColorGenerator::BasicColorGenerator(const glm::vec4& minStartColor,
                                         const glm::vec4& maxStartColor,
                                         const glm::vec4& minEndColor,
                                         const glm::vec4& maxEndColor) noexcept
  : m_minStartColor{minStartColor},
    m_maxStartColor{maxStartColor},
    m_minEndColor{minEndColor},
    m_maxEndColor{maxEndColor}
{
}

auto BasicColorGenerator::Generate([[maybe_unused]] const double dt,
                                   ParticleData* const particleData,
                                   // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
                                   const size_t startId,
                                   const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetStartColor(i, glm::linearRand(m_minStartColor, m_maxStartColor));
    particleData->SetEndColor(i, glm::linearRand(m_minEndColor, m_maxEndColor));
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
BasicVelocityGenerator::BasicVelocityGenerator(const glm::vec4& minStartVelocity,
                                               const glm::vec4& maxStartVelocity) noexcept
  : m_minStartVelocity{minStartVelocity}, m_maxStartVelocity{maxStartVelocity}
{
}

auto BasicVelocityGenerator::Generate([[maybe_unused]] const double dt,
                                      ParticleData* const particleData,
                                      // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
                                      const size_t startId,
                                      const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetVelocity(i, glm::linearRand(m_minStartVelocity, m_maxStartVelocity));
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
SphereVelocityGenerator::SphereVelocityGenerator(const float minVelocity,
                                                 const float maxVelocity) noexcept
  : m_minVelocity{minVelocity}, m_maxVelocity{maxVelocity}
{
}

auto SphereVelocityGenerator::Generate([[maybe_unused]] const double dt,
                                       ParticleData* const particleData,
                                       // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
                                       const size_t startId,
                                       const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto phi      = static_cast<float>(glm::linearRand(-M_PI, M_PI));
    const auto theta    = static_cast<float>(glm::linearRand(-M_PI, M_PI));
    const auto velocity = glm::linearRand(m_minVelocity, m_maxVelocity);
    const auto radius   = velocity * std::sin(phi);

    particleData->SetVelocity(i,
                              {radius * std::cos(theta),
                               radius * std::sin(theta),
                               0.0F, //v * std::cos(phi),
                               // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
                               particleData->GetVelocity(i).w});
  }
}

VelocityFromPositionGenerator::VelocityFromPositionGenerator(
    const glm::vec4& offset,
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    const float minScale,
    const float maxScale) noexcept
  : m_offset{offset}, m_minScale{minScale}, m_maxScale{maxScale}
{
}

auto VelocityFromPositionGenerator::Generate([[maybe_unused]] const double dt,
                                             ParticleData* const particleData,
                                             // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
                                             const size_t startId,
                                             const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto scale = glm::linearRand(m_minScale, m_maxScale);
    const auto vel   = glm::vec4{particleData->GetPosition(i) - m_offset};
    particleData->SetVelocity(i, scale * vel);
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
BasicTimeGenerator::BasicTimeGenerator(const float minTime, const float maxTime) noexcept
  : m_minTime{minTime}, m_maxTime{maxTime}
{
}

auto BasicTimeGenerator::Generate([[maybe_unused]] const double dt,
                                  ParticleData* const particleData,
                                  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
                                  const size_t startId,
                                  const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto xyTime = glm::linearRand(m_minTime, m_maxTime);

    particleData->SetTime(i, {xyTime, xyTime, 0.0F, 1.0F / xyTime});
  }
}

} // namespace PARTICLES::GENERATORS
