#include "particleUpdaters.h"

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>

namespace particles::updaters
{

auto EulerUpdater::update(const double dt, ParticleData* const p) -> void
{
  const auto globalA = glm::vec4{dt * static_cast<double>(m_globalAcceleration.x),
                                 dt * static_cast<double>(m_globalAcceleration.y),
                                 dt * static_cast<double>(m_globalAcceleration.z),
                                 0.0};

  const auto localDT = static_cast<float>(dt);
  const auto endId   = p->m_countAlive;

  glm::vec4* __restrict acc = p->m_acc.get();
  for (auto i = 0U; i < endId; ++i)
  {
    acc[i] += globalA;
  }

  glm::vec4* __restrict vel = p->m_vel.get();
  for (auto i = 0U; i < endId; ++i)
  {
    vel[i] += localDT * acc[i];
  }

  glm::vec4* __restrict pos = p->m_pos.get();
  for (auto i = 0U; i < endId; ++i)
  {
    pos[i] += localDT * vel[i];
  }
}

auto FloorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  glm::vec4* __restrict acc = p->m_acc.get();
  glm::vec4* __restrict vel = p->m_vel.get();
  glm::vec4* __restrict pos = p->m_pos.get();

  const auto endId = p->m_countAlive;
  for (auto i = 0U; i < endId; ++i)
  {
    if (pos[i].y < m_floorY)
    {
      auto force              = glm::vec4{p->m_acc[i]};
      const auto normalFactor = glm::dot(force, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      if (normalFactor < 0.0F)
      {
        force -= glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * normalFactor;
      }

      const auto velFactor = glm::dot(vel[i], glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      //if (velFactor < 0.0)
      vel[i] -= glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * (1.0F + m_bounceFactor) * velFactor;

      acc[i] = force;
    }
  }
}

auto AttractorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  glm::vec4* __restrict acc = p->m_acc.get();
  glm::vec4* __restrict pos = p->m_pos.get();

  const auto endId           = p->m_countAlive;
  const auto countAttractors = m_attractors.size();

  auto off  = glm::vec4{};
  auto dist = 0.0F;
  for (auto i = 0U; i < endId; ++i)
  {
    for (auto j = 0U; j < countAttractors; ++j)
    {
      off.x = m_attractors[j].x - pos[i].x;
      off.y = m_attractors[j].y - pos[i].y;
      off.z = m_attractors[j].z - pos[i].z;
      dist  = glm::dot(off, off);

      //if (fabs(dist) > 0.00001)
      dist = m_attractors[j].w / dist;

      acc[i] += off * dist;
    }
  }
}

auto BasicColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  glm::vec4* __restrict col      = p->m_col.get();
  glm::vec4* __restrict startCol = p->m_startCol.get();
  glm::vec4* __restrict endCol   = p->m_endCol.get();
  glm::vec4* __restrict t        = p->m_time.get();

  const auto endId = p->m_countAlive;

  for (auto i = 0U; i < endId; ++i)
  {
    col[i] = glm::mix(startCol[i], endCol[i], t[i].z);
  }
}

auto PosColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  glm::vec4* __restrict col      = p->m_col.get();
  glm::vec4* __restrict startCol = p->m_startCol.get();
  glm::vec4* __restrict endCol   = p->m_endCol.get();
  glm::vec4* __restrict t        = p->m_time.get();
  glm::vec4* __restrict pos      = p->m_pos.get();

  const auto endId = p->m_countAlive;
  const auto diffr = m_maxPos.x - m_minPos.x;
  const auto diffg = m_maxPos.y - m_minPos.y;
  const auto diffb = m_maxPos.z - m_minPos.z;

  auto scaler = 0.0F;
  auto scaleg = 0.0F;
  auto scaleb = 0.0F;

  for (auto i = 0U; i < endId; ++i)
  {
    scaler   = (pos[i].x - m_minPos.x) / diffr;
    scaleg   = (pos[i].y - m_minPos.y) / diffg;
    scaleb   = (pos[i].z - m_minPos.z) / diffb;
    col[i].r = scaler; // glm::mix(p->m_startCol[i].r, p->m_endCol[i].r, scaler);
    col[i].g = scaleg; // glm::mix(p->m_startCol[i].g, p->m_endCol[i].g, scaleg);
    col[i].b = scaleb; // glm::mix(p->m_startCol[i].b, p->m_endCol[i].b, scaleb);
    col[i].a = glm::mix(startCol[i].a, endCol[i].a, t[i].z);
  }
}

auto VelColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  glm::vec4* __restrict col      = p->m_col.get();
  glm::vec4* __restrict startCol = p->m_startCol.get();
  glm::vec4* __restrict endCol   = p->m_endCol.get();
  glm::vec4* __restrict t        = p->m_time.get();
  glm::vec4* __restrict vel      = p->m_vel.get();

  const auto endId = p->m_countAlive;
  const auto diffr = m_maxVel.x - m_minVel.x;
  const auto diffg = m_maxVel.y - m_minVel.y;
  const auto diffb = m_maxVel.z - m_minVel.z;

  auto scaler = 0.0F;
  auto scaleg = 0.0F;
  auto scaleb = 0.0F;
  for (auto i = 0U; i < endId; ++i)
  {
    scaler   = (vel[i].x - m_minVel.x) / diffr;
    scaleg   = (vel[i].y - m_minVel.y) / diffg;
    scaleb   = (vel[i].z - m_minVel.z) / diffb;
    col[i].r = scaler; // glm::mix(p->m_startCol[i].r, p->m_endCol[i].r, scaler);
    col[i].g = scaleg; // glm::mix(p->m_startCol[i].g, p->m_endCol[i].g, scaleg);
    col[i].b = scaleb; // glm::mix(p->m_startCol[i].b, p->m_endCol[i].b, scaleb);
    col[i].a = glm::mix(startCol[i].a, endCol[i].a, t[i].z);
  }
}

auto BasicTimeUpdater::update(const double dt, ParticleData* const p) -> void
{
  auto endId = p->m_countAlive;

  if (endId == 0)
  {
    return;
  }

  const auto localDT      = static_cast<float>(dt);
  glm::vec4* __restrict t = p->m_time.get();

  for (auto i = 0U; i < endId; ++i)
  {
    t[i].x -= localDT;
    // interpolation: from 0 (start of life) till 1 (end of life)
    t[i].z = 1.0F - (t[i].x * t[i].w); // .w is 1.0/max life time

    if (t[i].x < 0.0F)
    {
      p->kill(i);
      endId = p->m_countAlive < p->m_count ? p->m_countAlive : p->m_count;
    }
  }
}

} // namespace particles::updaters
