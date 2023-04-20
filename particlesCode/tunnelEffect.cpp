#include "tunnelEffect.h"

#include "glm/glm.hpp"

#include <cmath>

auto TunnelEffect::initialize(const size_t numParticles) -> bool
{
  //
  // particles
  //
  const auto numParticlesToUse = 0 == numParticles ? 10000 : numParticles;
  m_system                     = std::make_shared<particles::ParticleSystem>(numParticlesToUse);

  //
  // emitter:
  //
  auto particleEmitter = std::make_shared<particles::ParticleEmitter>();
  {
    particleEmitter->m_emitRate = static_cast<float>(numParticlesToUse) * 0.45F;

    // pos:
    m_posGenerator           = std::make_shared<particles::generators::RoundPosGen>();
    m_posGenerator->m_center = glm::vec4{0.0, 0.0, 0.0, 0.0};
    m_posGenerator->m_radX   = 0.15F;
    m_posGenerator->m_radY   = 0.15F;
    particleEmitter->addGenerator(m_posGenerator);

    m_colGenerator                = std::make_shared<particles::generators::BasicColorGen>();
    m_colGenerator->m_minStartCol = glm::vec4{0.7, 0.0, 0.7, 1.0};
    m_colGenerator->m_maxStartCol = glm::vec4{1.0, 1.0, 1.0, 1.0};
    m_colGenerator->m_minEndCol   = glm::vec4{0.5, 0.0, 0.6, 0.0};
    m_colGenerator->m_maxEndCol   = glm::vec4{0.7, 0.5, 1.0, 0.0};
    particleEmitter->addGenerator(m_colGenerator);

    auto velGenerator           = std::make_shared<particles::generators::BasicVelGen>();
    velGenerator->m_minStartVel = glm::vec4{0.0F, 0.0F, 0.15F, 0.0F};
    velGenerator->m_maxStartVel = glm::vec4{0.0F, 0.0F, 0.45F, 0.0F};
    particleEmitter->addGenerator(velGenerator);

    auto timeGenerator       = std::make_shared<particles::generators::BasicTimeGen>();
    timeGenerator->m_minTime = 1.0;
    timeGenerator->m_maxTime = 3.5;
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  auto timeUpdater = std::make_shared<particles::updaters::BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater = std::make_shared<particles::updaters::BasicColorUpdater>();
  //colorUpdater->m_minPos = glm::vec4{ -1.0f };
  //colorUpdater->m_maxPos = glm::vec4{ 1.0f };
  m_system->addUpdater(colorUpdater);

  auto eulerUpdater                  = std::make_shared<particles::updaters::EulerUpdater>();
  eulerUpdater->m_globalAcceleration = glm::vec4{0.0, 0.0, 0.0, 0.0};
  m_system->addUpdater(eulerUpdater);

  return true;
}

auto TunnelEffect::cpuUpdate(const double dt) -> void
{
  m_system->update(dt);
}
