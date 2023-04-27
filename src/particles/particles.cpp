#include "particles.h"

#include <algorithm>
#include <cassert>

namespace PARTICLES
{

ParticleData::ParticleData(const size_t count) noexcept
  : m_count{count},
    m_pos(count, glm::vec4{0.0F}),
    m_vel(count, glm::vec4{0.0F}),
    m_acc(count, glm::vec4{0.0F}),
    m_col(count, glm::vec4{0.0F}),
    m_startCol(count, glm::vec4{0.0F}),
    m_endCol(count, glm::vec4{0.0F}),
    m_time(count, glm::vec4{0.0F}),
    m_alive(count, false)
{
}

auto ParticleData::Kill(const size_t id) -> void
{
  //if (m_countAlive > 0) // maybe this if can be removed?
  {
    m_alive[id] = false;
    SwapData(id, m_countAlive - 1);
    --m_countAlive;
  }
}

auto ParticleData::Wake(const size_t id) -> void
{
  //if (m_countAlive < m_count) // maybe this 'if' can be removed?
  {
    m_alive[id] = true;
    //swapData(id, m_countAlive);
    ++m_countAlive;
  }
}

auto ParticleData::SwapData(const size_t a, const size_t b) -> void
{
  /*std::swap(m_pos[a], m_pos[b]);
    std::swap(m_col[a], m_col[b]);
    std::swap(m_startCol[a], m_startCol[b]);
    std::swap(m_endCol[a], m_endCol[b]);
    std::swap(m_vel[a], m_vel[b]);
    std::swap(m_acc[a], m_acc[b]);
    std::swap(m_time[a], m_time[b]);
    std::swap(m_alive[a], m_alive[b]);*/
  m_pos[a]      = m_pos[b];
  m_col[a]      = m_col[b];
  m_startCol[a] = m_startCol[b];
  m_endCol[a]   = m_endCol[b];
  m_vel[a]      = m_vel[b];
  m_acc[a]      = m_acc[b];
  m_time[a]     = m_time[b];
  //m_alive[a] = m_alive[b];*/
}

auto ParticleData::ComputeMemoryUsage(const ParticleData& particleData) -> size_t
{
  return particleData.m_count * ((7 * sizeof(glm::vec4)) + (sizeof(bool)) + (sizeof(size_t) * 2));
}

////////////////////////////////////////////////////////////////////////////////
// ParticleEmitter class

auto ParticleEmitter::Emit(const double dt, ParticleData* const particleData) noexcept -> void
{
  const auto maxNewParticles = static_cast<size_t>(dt * static_cast<double>(m_emitRate));
  const auto startId         = particleData->GetAliveCount();
  const auto endId           = std::min(startId + maxNewParticles, particleData->GetCount() - 1);

  for (auto& gen : m_generators)
  {
    gen->Generate(dt, particleData, startId, endId);
  }

  for (auto i = startId; i < endId; ++i)
  {
    particleData->Wake(i);
  }
}

////////////////////////////////////////////////////////////////////////////////
// ParticleSystem class

////////////////////////////////////////////////////////////////////////////////
ParticleSystem::ParticleSystem(const size_t maxCount) : m_count{maxCount}, m_particles{maxCount}
{
}

auto ParticleSystem::Update(const double dt) -> void
{
  for (auto& em : m_emitters)
  {
    em->Emit(dt, &m_particles);
  }

  for (auto i = 0U; i < m_count; ++i)
  {
    m_particles.SetAcceleration(i, glm::vec4{0.0F});
  }

  for (auto& up : m_updaters)
  {
    up->Update(dt, &m_particles);
  }

  //ParticleData::CopyOnlyAlive(&m_particles, &m_aliveParticles);
}

auto ParticleSystem::Reset() -> void
{
  m_particles.Reset();
}

auto ParticleSystem::ComputeMemoryUsage(const ParticleSystem& particleSystem) noexcept -> size_t
{
  return 2 * ParticleData::ComputeMemoryUsage(particleSystem.m_particles);
}

} // namespace PARTICLES
