#include "particles.h"

#include <algorithm>
#include <cassert>

namespace particles
{

auto ParticleData::generate(const size_t maxSize) -> void
{
  m_count      = maxSize;
  m_countAlive = 0;

  m_pos = std::make_unique<glm::vec4[]>(maxSize);
  m_col = std::make_unique<glm::vec4[]>(maxSize);
  m_startCol = std::make_unique<glm::vec4[]>(maxSize);
  m_endCol = std::make_unique<glm::vec4[]>(maxSize);
  m_vel = std::make_unique<glm::vec4[]>(maxSize);
  m_acc = std::make_unique<glm::vec4[]>(maxSize);
  m_time = std::make_unique<glm::vec4[]>(maxSize);
  m_alive = std::make_unique<bool[]>(maxSize);
}

auto ParticleData::kill(const size_t id) -> void
{
  //if (m_countAlive > 0) // maybe this if can be removed?
  {
    m_alive[id] = false;
    swapData(id, m_countAlive - 1);
    --m_countAlive;
  }
}

auto ParticleData::wake(const size_t id) -> void
{
  //if (m_countAlive < m_count) // maybe this if can be removed?
  {
    m_alive[id] = true;
    //swapData(id, m_countAlive);
    ++m_countAlive;
  }
}

auto ParticleData::swapData(const size_t a, const size_t b) -> void
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

auto ParticleData::copyOnlyAlive(const ParticleData* source, ParticleData* const destination)
    -> void
{
  assert(source->m_count == destination->m_count);

  size_t id = 0;
  for (auto i = 0U; i < source->m_countAlive; ++i)
  {
    //if (source->m_alive[i])
    {
      destination->m_pos[id]      = source->m_pos[i];
      destination->m_col[id]      = source->m_col[i];
      destination->m_startCol[id] = source->m_startCol[i];
      destination->m_endCol[id]   = source->m_endCol[i];
      destination->m_vel[id]      = source->m_vel[i];
      destination->m_acc[id]      = source->m_acc[i];
      destination->m_time[id]     = source->m_time[i];
      destination->m_alive[id]    = true;
      ++id;
    }
  }

  destination->m_countAlive = id;
}

auto ParticleData::computeMemoryUsage(const ParticleData& p) -> size_t
{
  return p.m_count * ((7 * sizeof(glm::vec4)) + sizeof(bool)) + (sizeof(size_t) * 2);
}

////////////////////////////////////////////////////////////////////////////////
// ParticleEmitter class

auto ParticleEmitter::emit(const double dt, ParticleData* const p) -> void
{
  const auto maxNewParticles = static_cast<size_t>(dt * static_cast<double>(m_emitRate));
  const auto startId         = p->GetAliveCount();
  const auto endId           = std::min(startId + maxNewParticles, p->GetCount() - 1);

  for (auto& gen : m_generators)
  {
    gen->generate(dt, p, startId, endId);
  }

  for (auto i = startId; i < endId; ++i)
  {
    p->wake(i);
  }
}

////////////////////////////////////////////////////////////////////////////////
// ParticleSystem class

////////////////////////////////////////////////////////////////////////////////
ParticleSystem::ParticleSystem(const size_t maxCount) : m_count{maxCount}
{
  m_particles.generate(maxCount);
  m_aliveParticles.generate(maxCount);
  m_particles.SetAllDead();
}

auto ParticleSystem::update(const double dt) -> void
{
  for (auto& em : m_emitters)
  {
    em->emit(dt, &m_particles);
  }

  for (auto i = 0U; i < m_count; ++i)
  {
    m_particles.SetAcceleration(i, glm::vec4{0.0F});
  }

  for (auto& up : m_updaters)
  {
    up->update(dt, &m_particles);
  }

  //ParticleData::copyOnlyAlive(&m_particles, &m_aliveParticles);
}

auto ParticleSystem::reset() -> void
{
  m_particles.reset();
}

auto ParticleSystem::computeMemoryUsage(const ParticleSystem& p) -> size_t
{
  return 2 * ParticleData::computeMemoryUsage(p.m_particles);
}

} // namespace particles
