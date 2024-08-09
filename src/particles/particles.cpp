module;

#include <algorithm>
#include <cassert>
#include <glm/vec4.hpp>

module Particles.Particles;

namespace PARTICLES
{

ParticleData::ParticleData(const size_t count) noexcept
  : m_count{count},
    m_position(count, glm::vec4{0.0F}),
    m_velocity(count, glm::vec4{0.0F}),
    m_acceleration(count, glm::vec4{0.0F}),
    m_color(count, glm::vec4{0.0F}),
    m_startColor(count, glm::vec4{0.0F}),
    m_endColor(count, glm::vec4{0.0F}),
    m_time(count, glm::vec4{0.0F}),
    m_alive(count, false)
{
}

auto ParticleData::Kill(const size_t id) noexcept -> void
{
  //if (m_countAlive > 0) // maybe this if can be removed?
  {
    m_alive[id] = false;
    SwapData(id, m_countAlive - 1);
    --m_countAlive;
  }
}

auto ParticleData::Wake(const size_t id) noexcept -> void
{
  //if (m_countAlive < m_count) // maybe this 'if' can be removed?
  {
    m_alive[id] = true;
    //swapData(id, m_countAlive);
    ++m_countAlive;
  }
}

auto ParticleData::SwapData(const size_t a, const size_t b) noexcept -> void
{
  /*std::swap(m_pos[a], m_pos[b]);
    std::swap(m_col[a], m_col[b]);
    std::swap(m_startCol[a], m_startCol[b]);
    std::swap(m_endCol[a], m_endCol[b]);
    std::swap(m_vel[a], m_vel[b]);
    std::swap(m_acc[a], m_acc[b]);
    std::swap(m_time[a], m_time[b]);
    std::swap(m_alive[a], m_alive[b]);*/
  m_position[a]     = m_position[b];
  m_color[a]        = m_color[b];
  m_startColor[a]   = m_startColor[b];
  m_endColor[a]     = m_endColor[b];
  m_velocity[a]     = m_velocity[b];
  m_acceleration[a] = m_acceleration[b];
  m_time[a]         = m_time[b];
  //m_alive[a] = m_alive[b];*/
}

////////////////////////////////////////////////////////////////////////////////
// ParticleEmitter class

auto ParticleEmitter::Emit(const double dt, ParticleData& particleData) noexcept -> void
{
  const auto maxNewParticles = GetMaxAllowedNewParticles(dt, particleData);
  const auto startId         = particleData.GetAliveCount();
  const auto endId           = std::min(startId + maxNewParticles, particleData.GetCount() - 1);

  for (auto& gen : m_generators)
  {
    gen->Generate(dt, particleData, {.start = startId, .end = endId});
  }

  for (auto i = startId; i < endId; ++i)
  {
    particleData.Wake(i);
  }
}

auto ParticleEmitter::GetMaxAllowedNewParticles(
    const double dt, const ParticleData& particleData) const noexcept -> size_t
{
  const auto requestedNewParticles  = static_cast<size_t>(dt * static_cast<double>(m_emitRate));
  const auto newTotalAliveParticles = requestedNewParticles + particleData.GetAliveCount();
  if (newTotalAliveParticles <= m_maxNumAliveParticles)
  {
    return requestedNewParticles;
  }

  return requestedNewParticles - (newTotalAliveParticles - m_maxNumAliveParticles);
}

////////////////////////////////////////////////////////////////////////////////
// ParticleSystem class

////////////////////////////////////////////////////////////////////////////////
ParticleSystem::ParticleSystem(const size_t maxCount) : m_count{maxCount}, m_particles{maxCount}
{
}

auto ParticleSystem::Update(const double dt) noexcept -> void
{
  for (auto& em : m_emitters)
  {
    em->Emit(dt, m_particles);
  }

  for (auto i = 0U; i < m_count; ++i)
  {
    m_particles.SetAcceleration(i, glm::vec4{0.0F});
  }

  for (auto& up : m_updaters)
  {
    up->Update(dt, m_particles);
  }
}

auto ParticleSystem::Reset() noexcept -> void
{
  m_particles.Reset();
}

auto ParticleSystem::ComputeMemoryUsage(const ParticleSystem& particleSystem) noexcept -> size_t
{
  return 2 * ParticleData::ComputeMemoryUsage(particleSystem.m_particles);
}

} // namespace PARTICLES
