#include "attractorEffect.h"

#include <cmath>

auto AttractorEffect::initialize(const size_t numParticles) -> bool
{
  //
  // particles
  //
  const auto numParticlesToUse = 0 == numParticles ? 250000 : numParticles;
  m_system                     = std::make_shared<particles::ParticleSystem>(numParticlesToUse);

  //
  // common
  //
  m_colGenerator                = std::make_shared<particles::generators::BasicColorGen>();
  m_colGenerator->m_minStartCol = glm::vec4{0.99, 0.99, 0.99, 1.0};
  m_colGenerator->m_maxStartCol = glm::vec4{0.99, 0.99, 1.0, 1.0};
  m_colGenerator->m_minEndCol   = glm::vec4{0.99, 0.99, 0.99, 0.0};
  m_colGenerator->m_maxEndCol   = glm::vec4{0.99, 0.99, 1.0, 0.25};

  auto velGenerator      = std::make_shared<particles::generators::SphereVelGen>();
  velGenerator->m_minVel = 0.1F;
  velGenerator->m_maxVel = 0.1F;

  auto timeGenerator       = std::make_shared<particles::generators::BasicTimeGen>();
  timeGenerator->m_minTime = 1.6F;
  timeGenerator->m_maxTime = 4.0F;

  //
  // emitter 1:
  //
  auto particleEmitter = std::make_shared<particles::ParticleEmitter>();
  {
    particleEmitter->m_emitRate = static_cast<float>(numParticlesToUse) * 0.1F;

    // pos:
    m_posGenerators[0]                      = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerators[0]->m_pos               = glm::vec4{0.0, 0.0, -0.25, 0.0};
    m_posGenerators[0]->m_maxStartPosOffset = glm::vec4{0.0, 0.0, 0.0, 0.0};
    particleEmitter->addGenerator(m_posGenerators[0]);

    particleEmitter->addGenerator(m_colGenerator);
    particleEmitter->addGenerator(velGenerator);
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  //
  // emitter 2:
  //
  auto particleEmitter2 = std::make_shared<particles::ParticleEmitter>();
  {
    particleEmitter2->m_emitRate = static_cast<float>(numParticlesToUse) * 0.1F;

    m_posGenerators[1]                      = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerators[1]->m_pos               = glm::vec4{0.0, 0.0, 0.25, 0.0};
    m_posGenerators[1]->m_maxStartPosOffset = glm::vec4{0.0, 0.0, 0.0, 0.0};
    particleEmitter2->addGenerator(m_posGenerators[1]);

    particleEmitter2->addGenerator(m_colGenerator);
    particleEmitter2->addGenerator(velGenerator);
    particleEmitter2->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter2);

  //
  // emitter 3:
  //
  auto particleEmitter3 = std::make_shared<particles::ParticleEmitter>();
  {
    particleEmitter3->m_emitRate = static_cast<float>(numParticlesToUse) * 0.1F;

    m_posGenerators[2]                      = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerators[2]->m_pos               = glm::vec4{0.0, 0.0, 0.25, 0.0};
    m_posGenerators[2]->m_maxStartPosOffset = glm::vec4{0.0, 0.0, 0.0, 0.0};
    particleEmitter3->addGenerator(m_posGenerators[2]);

    particleEmitter3->addGenerator(m_colGenerator);
    particleEmitter3->addGenerator(velGenerator);
    particleEmitter3->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter3);

  //
  // updaters:
  //
  auto timeUpdater = std::make_shared<particles::updaters::BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater      = std::make_shared<particles::updaters::VelColorUpdater>();
  colorUpdater->m_minVel = glm::vec4{-0.5F, -0.5F, -0.5F, 0.0F};
  colorUpdater->m_maxVel = glm::vec4{2.0F, 2.0F, 2.0F, 2.0F};
  m_system->addUpdater(colorUpdater);

  m_attractors = std::make_shared<particles::updaters::AttractorUpdater>();
  m_attractors->add(glm::vec4{0.0, 0.0, 0.75, 1.0});
  m_attractors->add(glm::vec4{0.0, 0.0, -0.75, 1.0});
  m_attractors->add(glm::vec4{0.0, 0.75, 0.0, 1.0});
  m_attractors->add(glm::vec4{0.0, -0.75, 0.0, 1.0});
  m_system->addUpdater(m_attractors);

  auto eulerUpdater                  = std::make_shared<particles::updaters::EulerUpdater>();
  eulerUpdater->m_globalAcceleration = glm::vec4{0.0, 0.0, 0.0, 0.0};
  m_system->addUpdater(eulerUpdater);

  m_zScale = 1.0F;

  return true;
}

auto AttractorEffect::update(const double dt) -> void
{
  static auto s_time = 0.0F;
  s_time += static_cast<float>(dt);

  m_posGenerators[0]->m_pos.x = 0.15F * std::sin(s_time * 2.5F);
  m_posGenerators[0]->m_pos.y = 0.15F * std::cos(s_time * 2.5F);
  m_posGenerators[0]->m_pos.z = m_zScale * (0.25F * std::cos(s_time * 2.5F));

  m_posGenerators[1]->m_pos.x = -0.15F * std::sin(s_time * 2.0F);
  m_posGenerators[1]->m_pos.y = 0.15f * std::cos(s_time * 2.0F);
  m_posGenerators[1]->m_pos.z = m_zScale * (0.25F * std::cos(s_time * 1.5F));

  m_posGenerators[2]->m_pos.x = -0.15F * std::sin(s_time * 1.5F);
  m_posGenerators[2]->m_pos.y = 0.15F * std::cos(s_time * 2.5F);
  m_posGenerators[2]->m_pos.z = m_zScale * (0.25F * std::cos(s_time * 1.75F));
}

auto AttractorEffect::cpuUpdate(const double dt) -> void
{
  m_system->update(dt);
}
