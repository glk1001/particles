#include "particleUpdaters.h"

#include <glm/common.hpp>
#include <glm/gtc/random.hpp>

namespace PARTICLES::UPDATERS
{

auto EulerUpdater::update(const double dt, ParticleData* const particleData) -> void
{
  const auto globalA = glm::vec4{dt * static_cast<double>(m_globalAcceleration.x),
                                 dt * static_cast<double>(m_globalAcceleration.y),
                                 dt * static_cast<double>(m_globalAcceleration.z),
                                 0.0};

  const auto localDT = static_cast<float>(dt);
  const auto endId   = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->IncAcceleration(i, globalA);
  }

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->IncVelocity(i, localDT * particleData->GetAcceleration(i));
  }

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->IncPosition(i, localDT * particleData->GetVelocity(i));
  }
}

auto FloorUpdater::update([[maybe_unused]] const double dt, ParticleData* const particleData)
    -> void
{
  const auto endId = particleData->GetAliveCount();
  for (auto i = 0U; i < endId; ++i)
  {
    if (particleData->GetPosition(i).y < m_floorY)
    {
      auto force              = glm::vec4{particleData->GetAcceleration(i)};
      const auto normalFactor = glm::dot(force, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      if (normalFactor < 0.0F)
      {
        force -= glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * normalFactor;
      }

      const auto velFactor =
          glm::dot(particleData->GetVelocity(i), glm::vec4(0.0F, 1.0F, 0.0F, 0.0F));
      //if (velFactor < 0.0)
      particleData->DecVelocity(
          i, glm::vec4(0.0F, 1.0F, 0.0F, 0.0F) * (1.0F + m_bounceFactor) * velFactor);

      particleData->SetAcceleration(i, force);
    }
  }
}

auto AttractorUpdater::update([[maybe_unused]] const double dt, ParticleData* const particleData)
    -> void
{
  const auto endId           = particleData->GetAliveCount();
  const auto countAttractors = m_attractors.size();

  auto off  = glm::vec4{};
  auto dist = 0.0F;
  for (auto i = 0U; i < endId; ++i)
  {
    for (auto j = 0U; j < countAttractors; ++j)
    {
      off.x = m_attractors[j].x - particleData->GetPosition(i).x;
      off.y = m_attractors[j].y - particleData->GetPosition(i).y;
      off.z = m_attractors[j].z - particleData->GetPosition(i).z;
      dist  = glm::dot(off, off);

      //if (fabs(dist) > 0.00001)
      dist = m_attractors[j].w / dist;

      particleData->IncAcceleration(i, off * dist);
    }
  }
}

auto BasicColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const particleData)
    -> void
{
  const auto endId = particleData->GetAliveCount();

  for (auto i = 0U; i < endId; ++i)
  {
    particleData->SetColor(i,
                           glm::mix(particleData->GetStartColor(i),
                                    particleData->GetEndColor(i),
                                    particleData->GetTime(i).z));
  }
}

auto PosColorUpdater::update([[maybe_unused]] const double dt, ParticleData* const particleData)
    -> void
{
  const auto endId = particleData->GetAliveCount();
  const auto diffr = m_maxPos.x - m_minPos.x;
  const auto diffg = m_maxPos.y - m_minPos.y;
  const auto diffb = m_maxPos.z - m_minPos.z;

  auto scaler = 0.0F;
  auto scaleg = 0.0F;
  auto scaleb = 0.0F;

  for (auto i = 0U; i < endId; ++i)
  {
    scaler = (particleData->GetPosition(i).x - m_minPos.x) / diffr;
    scaleg = (particleData->GetPosition(i).y - m_minPos.y) / diffg;
    scaleb = (particleData->GetPosition(i).z - m_minPos.z) / diffb;
    particleData->SetColor(
        i,
        {scaler, // glm::mix(particleData->m_startCol[i].r, particleData->m_endCol[i].r, scaler);
         scaleg, // glm::mix(particleData->m_startCol[i].g, particleData->m_endCol[i].g, scaleg);
         scaleb, // glm::mix(particleData->m_startCol[i].b, particleData->m_endCol[i].b, scaleb);
         glm::mix(particleData->GetStartColor(i).a,
                  particleData->GetEndColor(i).a,
                  particleData->GetTime(i).z)});
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

auto BasicTimeUpdater::update(const double dt, ParticleData* const particleData) -> void
{
  auto endId = particleData->GetAliveCount();

  if (endId == 0)
  {
    return;
  }

  const auto localDT = static_cast<float>(dt);

  for (auto i = 0U; i < endId; ++i)
  {
    const auto newXTime = particleData->GetTime(i).x - localDT;

    // Interpolation: From 0 (start of life) till 1 (end of life)
    const auto newZTime =
        1.0F - (particleData->GetTime(i).x * particleData->GetTime(i).w); // .w is 1.0/max lifetime

    particleData->SetTime(
        i, {newXTime, particleData->GetTime(i).y, newZTime, particleData->GetTime(i).w});

    if (newXTime < 0.0F)
    {
      particleData->kill(i);
      endId = particleData->GetAliveCount() < particleData->GetCount()
                  ? particleData->GetAliveCount()
                  : particleData->GetCount();
    }
  }
}

} // namespace PARTICLES::UPDATERS
