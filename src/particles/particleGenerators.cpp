#include "particleGenerators.h"

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795f
#define M_2_PI 6.28318530717958647692528676655901f // PI*2
#endif

namespace PARTICLES::GENERATORS
{

auto BoxPosGen::generate([[maybe_unused]] const double dt,
                         ParticleData* const particleData,
                         const size_t startId,
                         const size_t endId) -> void
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

auto RoundPosGen::generate([[maybe_unused]] const double dt,
                           ParticleData* const particleData,
                           const size_t startId,
                           const size_t endId) -> void
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

auto BasicColorGen::generate([[maybe_unused]] const double dt,
                             ParticleData* const particleData,
                             const size_t startId,
                             const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetStartColor(i, glm::linearRand(m_minStartCol, m_maxStartCol));
    particleData->SetEndColor(i, glm::linearRand(m_minEndCol, m_maxEndCol));
  }
}

auto BasicVelGen::generate([[maybe_unused]] const double dt,
                           ParticleData* const particleData,
                           const size_t startId,
                           const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    particleData->SetVelocity(i, glm::linearRand(m_minStartVel, m_maxStartVel));
  }
}

auto SphereVelGen::generate([[maybe_unused]] const double dt,
                            ParticleData* const particleData,
                            const size_t startId,
                            const size_t endId) -> void
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

auto VelFromPosGen::generate([[maybe_unused]] const double dt,
                             ParticleData* const particleData,
                             const size_t startId,
                             const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto scale = glm::linearRand(m_minScale, m_maxScale);
    const auto vel   = glm::vec4{particleData->GetPosition(i) - m_offset};
    particleData->SetVelocity(i, scale * vel);
  }
}

auto BasicTimeGen::generate([[maybe_unused]] const double dt,
                            ParticleData* const particleData,
                            const size_t startId,
                            const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto xyTime = glm::linearRand(m_minTime, m_maxTime);

    particleData->SetTime(i, {xyTime, xyTime, 0.0F, 1.0F / particleData->GetTime(i).x});
  }
}

} // namespace PARTICLES::GENERATORS
