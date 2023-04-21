#include "attractorEffect.h"

namespace particles::EFFECTS
{

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
  m_colGenerator = std::make_shared<particles::generators::BasicColorGen>();
  m_colGenerator->SetMinMaxStartColors(glm::vec4{0.99, 0.99, 0.99, 1.0},
                                       glm::vec4{0.99, 0.99, 1.0, 1.0});
  m_colGenerator->SetMinMaxEndColors(glm::vec4{0.99, 0.99, 0.99, 0.0},
                                     glm::vec4{0.99, 0.99, 1.0, 0.25});

  auto velGenerator      = std::make_shared<particles::generators::SphereVelGen>();
  velGenerator->m_minVel = 0.1F;
  velGenerator->m_maxVel = 0.1F;

  auto timeGenerator = std::make_shared<particles::generators::BasicTimeGen>();
  timeGenerator->SetMinMaxTime(1.6F, 4.0F);

  //
  // emitter 1:
  //
  auto particleEmitter = std::make_shared<particles::ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerators[0] = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerators[0]->SetPosition(glm::vec4{0.0, 0.0, -0.25, 0.0});
    m_posGenerators[0]->SetMaxStartPositionOffset(glm::vec4{0.0, 0.0, 0.0, 0.0});
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
    particleEmitter2->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    m_posGenerators[1] = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerators[1]->SetPosition(glm::vec4{0.0, 0.0, 0.25, 0.0});
    m_posGenerators[1]->SetMaxStartPositionOffset(glm::vec4{0.0, 0.0, 0.0, 0.0});
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
    particleEmitter3->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    m_posGenerators[2] = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerators[2]->SetPosition(glm::vec4{0.0, 0.0, 0.25, 0.0});
    m_posGenerators[2]->SetMaxStartPositionOffset(glm::vec4{0.0, 0.0, 0.0, 0.0});
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
  m_attractors->add(glm::vec4{3.0, 0.0, 0.75, 1.0});
  m_attractors->add(glm::vec4{0.0, 1.0, -0.75, 1.0});
  m_attractors->add(glm::vec4{-0.40, 0.75, 0.0, 1.0});
  m_attractors->add(glm::vec4{-2.0, -0.75, 0.0, 1.0});
  m_system->addUpdater(m_attractors);

  auto eulerUpdater = std::make_shared<particles::updaters::EulerUpdater>();
  eulerUpdater->SetGlobalAcceleration(glm::vec4{0.0, 0.0, 0.0, 0.0});
  m_system->addUpdater(eulerUpdater);

  return true;
}

} // namespace particles::EFFECTS
