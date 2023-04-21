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
  const auto endId   = p->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    p->IncAcceleration(i, globalA);
  }

  for (auto i = 0U; i < endId; ++i)
  {
    p->IncVelocity(i, localDT * p->GetAcceleration(i));
  }

  for (auto i = 0U; i < endId; ++i)
  {
    p->IncPosition(i, localDT * p->GetVelocity(i));
  }
}

auto FloorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  const auto endId = p->GetAliveCount();
  for (auto i = 0U; i < endId; ++i)
  {
    if (p->GetPosition(i).y < m_floorY)
    {
      auto force              = glm::vec4{p->GetAcceleration(i)};
      const auto normalFactor = glm::dot(force, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      if (normalFactor < 0.0F)
      {
        force -= glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * normalFactor;
      }

      const auto velFactor = glm::dot(p->GetVelocity(i), glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      //if (velFactor < 0.0)
      p->DecVelocity(i, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * (1.0F + m_bounceFactor) * velFactor);

      p->SetAcceleration(i, force);
    }
  }
}

auto AttractorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  const auto endId           = p->GetAliveCount();
  const auto countAttractors = m_attractors.size();

  auto off  = glm::vec4{};
  auto dist = 0.0F;
  for (auto i = 0U; i < endId; ++i)
  {
    for (auto j = 0U; j < countAttractors; ++j)
    {
      off.x = m_attractors[j].x - p->GetPosition(i).x;
      off.y = m_attractors[j].y - p->GetPosition(i).y;
      off.z = m_attractors[j].z - p->GetPosition(i).z;
      dist  = glm::dot(off, off);

      //if (fabs(dist) > 0.00001)
      dist = m_attractors[j].w / dist;

      p->IncAcceleration(i, off * dist);
    }
  }
}

auto BasicColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  const auto endId = p->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    p->SetColor(i, glm::mix(p->GetStartColor(i), p->GetEndColor(i), p->GetTime(i).z));
  }
}

auto PosColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  const auto endId = p->GetAliveCount();
  const auto diffr = m_maxPos.x - m_minPos.x;
  const auto diffg = m_maxPos.y - m_minPos.y;
  const auto diffb = m_maxPos.z - m_minPos.z;

  auto scaler = 0.0F;
  auto scaleg = 0.0F;
  auto scaleb = 0.0F;

  for (auto i = 0U; i < endId; ++i)
  {
    scaler = (p->GetPosition(i).x - m_minPos.x) / diffr;
    scaleg = (p->GetPosition(i).y - m_minPos.y) / diffg;
    scaleb = (p->GetPosition(i).z - m_minPos.z) / diffb;
    p->SetColor(i,
                {scaler, // glm::mix(p->m_startCol[i].r, p->m_endCol[i].r, scaler);
                 scaleg, // glm::mix(p->m_startCol[i].g, p->m_endCol[i].g, scaleg);
                 scaleb, // glm::mix(p->m_startCol[i].b, p->m_endCol[i].b, scaleb);
                 glm::mix(p->GetStartColor(i).a, p->GetEndColor(i).a, p->GetTime(i).z)});
  }
}

auto VelColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const p) -> void
{
  const auto endId = p->GetAliveCount();
  const auto diffr = m_maxVel.x - m_minVel.x;
  const auto diffg = m_maxVel.y - m_minVel.y;
  const auto diffb = m_maxVel.z - m_minVel.z;

  auto scaler = 0.0F;
  auto scaleg = 0.0F;
  auto scaleb = 0.0F;
  for (auto i = 0U; i < endId; ++i)
  {
    scaler = (p->GetVelocity(i).x - m_minVel.x) / diffr;
    scaleg = (p->GetVelocity(i).y - m_minVel.y) / diffg;
    scaleb = (p->GetVelocity(i).z - m_minVel.z) / diffb;
    p->SetColor(i,
                {scaler, // glm::mix(p->m_startCol[i].r, p->m_endCol[i].r, scaler);
                 scaleg, // glm::mix(p->m_startCol[i].g, p->m_endCol[i].g, scaleg);
                 scaleb, // glm::mix(p->m_startCol[i].b, p->m_endCol[i].b, scaleb);
                 glm::mix(p->GetStartColor(i).a, p->GetEndColor(i).a, p->GetTime(i).z)});
  }
}

auto BasicTimeUpdater::update(const double dt, ParticleData* const p) -> void
{
  auto endId = p->GetAliveCount();

  if (endId == 0)
  {
    return;
  }

  const auto localDT = static_cast<float>(dt);

  for (auto i = 0U; i < endId; ++i)
  {
    const auto newXTime = p->GetTime(i).x - localDT;

    // Interpolation: From 0 (start of life) till 1 (end of life)
    const auto newZTime = 1.0F - (p->GetTime(i).x * p->GetTime(i).w); // .w is 1.0/max lifetime

    p->SetTime(i, {newXTime, p->GetTime(i).y, newZTime, p->GetTime(i).w});

    if (newXTime < 0.0F)
    {
      p->kill(i);
      endId = p->GetAliveCount() < p->GetCount() ? p->GetAliveCount() : p->GetCount();
    }
  }
}

} // namespace particles::updaters
