#include "particle_generators.h"

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>

namespace PARTICLES::GENERATORS
{

BoxPosGen::BoxPosGen(const glm::vec4& position, const glm::vec4& maxStartPosOffset) noexcept
  : m_pos{position}, m_maxStartPosOffset{maxStartPosOffset}
{
}

auto BoxPosGen::Generate([[maybe_unused]] const double dt,
                         ParticleData* const particleData,
                         const size_t startId,
                         const size_t endId) noexcept -> void
{
  const auto posMin = glm::vec4{m_pos.x - m_maxStartPosOffset.x,
                                m_pos.y - m_maxStartPosOffset.y,
                                m_pos.z - m_maxStartPosOffset.z,
                                1.0};
  const auto posMax = glm::vec4{m_pos.x + m_maxStartPosOffset.x,
                                m_pos.y + m_maxStartPosOffset.y,
                                m_pos.z + m_maxStartPosOffset.z,
                                1.0};

  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetPosition(i, glm::linearRand(posMin, posMax));
  }
}

RoundPosGen::RoundPosGen(const glm::vec4& center, const double radX, const double radY) noexcept
  : m_center{center}, m_radX{static_cast<float>(radX)}, m_radY{static_cast<float>(radY)}
{
}

auto RoundPosGen::Generate([[maybe_unused]] const double dt,
                           ParticleData* const particleData,
                           const size_t startId,
                           const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    // TODO(glk) - Need '2.01' instead of '2.0' to cover small radial gap (see tunnel effect).
    const auto ang = glm::linearRand(0.0, M_PI * 2.01);
    particleData->SetPosition(i,
                              m_center + glm::vec4(static_cast<double>(m_radX) * std::sin(ang),
                                                   static_cast<double>(m_radY) * std::cos(ang),
                                                   0.0,
                                                   1.0));
  }
}

BasicColorGen::BasicColorGen(const glm::vec4& minStartColor,
                             const glm::vec4& maxStartColor,
                             const glm::vec4& minEndColor,
                             const glm::vec4& maxEndColor) noexcept
  : m_minStartCol{minStartColor},
    m_maxStartCol{maxStartColor},
    m_minEndCol{minEndColor},
    m_maxEndCol{maxEndColor}
{
}

auto BasicColorGen::Generate([[maybe_unused]] const double dt,
                             ParticleData* const particleData,
                             const size_t startId,
                             const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetStartColor(i, glm::linearRand(m_minStartCol, m_maxStartCol));
    particleData->SetEndColor(i, glm::linearRand(m_minEndCol, m_maxEndCol));
  }
}

BasicVelGen::BasicVelGen(const glm::vec4& minStartVelocity,
                         const glm::vec4& maxStartVelocity) noexcept
  : m_minStartVel{minStartVelocity}, m_maxStartVel{maxStartVelocity}
{
}

auto BasicVelGen::Generate([[maybe_unused]] const double dt,
                           ParticleData* const particleData,
                           const size_t startId,
                           const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetVelocity(i, glm::linearRand(m_minStartVel, m_maxStartVel));
  }
}

SphereVelGen::SphereVelGen(const float minVelocity, const float maxVelocity) noexcept
  : m_minVel{minVelocity}, m_maxVel{maxVelocity}
{
}

auto SphereVelGen::Generate([[maybe_unused]] const double dt,
                            ParticleData* const particleData,
                            const size_t startId,
                            const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto phi   = static_cast<float>(glm::linearRand(-M_PI, M_PI));
    const auto theta = static_cast<float>(glm::linearRand(-M_PI, M_PI));
    const auto v     = glm::linearRand(m_minVel, m_maxVel);
    const auto r     = v * std::sin(phi);

    particleData->SetVelocity(i,
                              {r * std::cos(theta),
                               r * std::sin(theta),
                               v * std::cos(phi),
                               particleData->GetVelocity(i).w});
  }
}

VelFromPosGen::VelFromPosGen(const glm::vec4& offset,
                             const float minScale,
                             const float maxScale) noexcept
  : m_offset{offset}, m_minScale{minScale}, m_maxScale{maxScale}
{
}

auto VelFromPosGen::Generate([[maybe_unused]] const double dt,
                             ParticleData* const particleData,
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

BasicTimeGen::BasicTimeGen(const float minTime, const float maxTime) noexcept
  : m_minTime{minTime}, m_maxTime{maxTime}
{
}

auto BasicTimeGen::Generate([[maybe_unused]] const double dt,
                            ParticleData* const particleData,
                            const size_t startId,
                            const size_t endId) noexcept -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto xyTime = glm::linearRand(m_minTime, m_maxTime);

    particleData->SetTime(i, {xyTime, xyTime, 0.0F, 1.0F / particleData->GetTime(i).x});
  }
}

} // namespace PARTICLES::GENERATORS
