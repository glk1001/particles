#include "particleGenerators.h"

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795f
#define M_2_PI 6.28318530717958647692528676655901f // PI*2
#endif

namespace particles::generators
{

auto BoxPosGen::generate([[maybe_unused]] const double dt,
                         ParticleData* const p,
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
    p->m_pos[i] = glm::linearRand(posMin, posMax);
  }
}

auto RoundPosGen::generate([[maybe_unused]] const double dt,
                           ParticleData* const p,
                           const size_t startId,
                           const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto ang = glm::linearRand(0.0, M_PI * 2.0);
    p->m_pos[i]    = m_center + glm::vec4(static_cast<double>(m_radX) * std::sin(ang),
                                       static_cast<double>(m_radY) * std::cos(ang),
                                       0.0,
                                       1.0);
  }
}

auto BasicColorGen::generate([[maybe_unused]] const double dt,
                             ParticleData* const p,
                             const size_t startId,
                             const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    p->m_startCol[i] = glm::linearRand(m_minStartCol, m_maxStartCol);
    p->m_endCol[i]   = glm::linearRand(m_minEndCol, m_maxEndCol);
  }
}

auto BasicVelGen::generate([[maybe_unused]] const double dt,
                           ParticleData* const p,
                           const size_t startId,
                           const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    p->m_vel[i] = glm::linearRand(m_minStartVel, m_maxStartVel);
  }
}

auto SphereVelGen::generate([[maybe_unused]] const double dt,
                            ParticleData* const p,
                            const size_t startId,
                            const size_t endId) -> void
{
  auto phi   = 0.0F;
  auto theta = 0.0F;
  auto v     = 0.0F;
  auto r     = 0.0F;
  for (auto i = startId; i < endId; ++i)
  {
    phi   = static_cast<float>(glm::linearRand(-M_PI, M_PI));
    theta = static_cast<float>(glm::linearRand(-M_PI, M_PI));
    v     = glm::linearRand(m_minVel, m_maxVel);

    r             = v * std::sin(phi);
    p->m_vel[i].z = v * std::cos(phi);
    p->m_vel[i].x = r * std::cos(theta);
    p->m_vel[i].y = r * std::sin(theta);
  }
}

auto VelFromPosGen::generate([[maybe_unused]] const double dt,
                             ParticleData* const p,
                             const size_t startId,
                             const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    const auto scale = glm::linearRand(m_minScale, m_maxScale);
    const auto vel   = glm::vec4{p->m_pos[i] - m_offset};
    p->m_vel[i]      = scale * vel;
  }
}

auto BasicTimeGen::generate([[maybe_unused]] const double dt,
                            ParticleData* const p,
                            const size_t startId,
                            const size_t endId) -> void
{
  for (auto i = startId; i < endId; ++i)
  {
    p->m_time[i].x = p->m_time[i].y = glm::linearRand(m_minTime, m_maxTime);
    p->m_time[i].z                  = 0.0F;
    p->m_time[i].w                  = 1.0F / p->m_time[i].x;
  }
}

} // namespace particles::generators
