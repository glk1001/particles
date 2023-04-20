#include "fountainEffect.h"

#include <cmath>

auto FountainEffect::initialize(const size_t numParticles) -> bool
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
    particleEmitter->m_emitRate = static_cast<float>(numParticlesToUse) * 0.25F;

    // pos:
    m_posGenerator                      = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerator->m_pos               = glm::vec4{0.0, 0.0, 0.0, 0.0};
    m_posGenerator->m_maxStartPosOffset = glm::vec4{0.0, 0.0, 0.0, 0.0};
    particleEmitter->addGenerator(m_posGenerator);

    m_colGenerator                = std::make_shared<particles::generators::BasicColorGen>();
    m_colGenerator->m_minStartCol = glm::vec4{0.7, 0.7, 0.7, 1.0};
    m_colGenerator->m_maxStartCol = glm::vec4{1.0, 1.0, 1.0, 1.0};
    m_colGenerator->m_minEndCol   = glm::vec4{0.5, 0.0, 0.6, 0.0};
    m_colGenerator->m_maxEndCol   = glm::vec4{0.7, 0.5, 1.0, 0.0};
    particleEmitter->addGenerator(m_colGenerator);

    auto velGenerator           = std::make_shared<particles::generators::BasicVelGen>();
    velGenerator->m_minStartVel = glm::vec4{-0.05F, 0.22F, -0.05F, 0.0F};
    velGenerator->m_maxStartVel = glm::vec4{0.05F, 0.25F, 0.05F, 0.0F};
    particleEmitter->addGenerator(velGenerator);

    auto timeGenerator       = std::make_shared<particles::generators::BasicTimeGen>();
    timeGenerator->m_minTime = 3.0F;
    timeGenerator->m_maxTime = 4.0F;
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  auto timeUpdater = std::make_shared<particles::updaters::BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater = std::make_shared<particles::updaters::BasicColorUpdater>();
  m_system->addUpdater(colorUpdater);

  m_eulerUpdater                       = std::make_shared<particles::updaters::EulerUpdater>();
  m_eulerUpdater->m_globalAcceleration = glm::vec4{0.0, -15.0, 0.0, 0.0};
  m_system->addUpdater(m_eulerUpdater);

  m_floorUpdater = std::make_shared<particles::updaters::FloorUpdater>();
  m_system->addUpdater(m_floorUpdater);

  return true;
}

auto FountainEffect::update(const double dt) -> void
{
  static double s_time = 0.0;
  s_time += dt;

  m_posGenerator->m_pos.x = 0.1F * std::sin(static_cast<float>(s_time) * 2.5F);
  m_posGenerator->m_pos.z = 0.1F * std::cos(static_cast<float>(s_time) * 2.5F);
}

auto FountainEffect::cpuUpdate(const double dt) -> void
{
  m_system->update(dt);
}
