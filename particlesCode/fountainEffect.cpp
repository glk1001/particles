#include "fountainEffect.h"

namespace particles::EFFECTS
{

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
    particleEmitter->SetEmitRate(0.25F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerator = std::make_shared<particles::generators::BoxPosGen>();
    m_posGenerator->SetPosition(glm::vec4{0.0, 0.0, 0.0, 0.0});
    m_posGenerator->SetMaxStartPositionOffset(glm::vec4{0.1, 0.1, 0.0, 0.0});
    particleEmitter->addGenerator(m_posGenerator);

    m_colGenerator = std::make_shared<particles::generators::BasicColorGen>();
    m_colGenerator->SetMinMaxStartColors(glm::vec4{0.5, 0.5, 0.5, 1.0},
                                         glm::vec4{1.0, 1.0, 1.0, 1.0});
    m_colGenerator->SetMinMaxEndColors(glm::vec4{0.5, 0.0, 0.6, 0.0},
                                       glm::vec4{0.7, 0.5, 1.0, 0.0});
    particleEmitter->addGenerator(m_colGenerator);

    auto velGenerator = std::make_shared<particles::generators::BasicVelGen>();
    velGenerator->SetMinMaxVelocity(glm::vec4{-0.5F, 0.052F, -0.05F, 0.0F},
                                    glm::vec4{0.5F, 0.25F, 0.05F, 0.0F});
    particleEmitter->addGenerator(velGenerator);

    auto timeGenerator = std::make_shared<particles::generators::BasicTimeGen>();
    timeGenerator->SetMinMaxTime(30.0F, 40.0F);
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  auto timeUpdater = std::make_shared<particles::updaters::BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater = std::make_shared<particles::updaters::BasicColorUpdater>();
  //colorUpdater->m_minVel = glm::vec4{0.0F, 0.0F, -0.0F, 0.0F};
  //colorUpdater->m_maxVel = glm::vec4{0.5F, 1.0F, -0.0F, 0.0F};
  m_system->addUpdater(colorUpdater);

  m_eulerUpdater = std::make_shared<particles::updaters::EulerUpdater>();
  m_eulerUpdater->SetGlobalAcceleration(glm::vec4{0.0, -2.0, 0.0, 0.0});
  m_system->addUpdater(m_eulerUpdater);

  m_floorUpdater                 = std::make_shared<particles::updaters::FloorUpdater>();
  m_floorUpdater->m_floorY       = -3.50F;
  m_floorUpdater->m_bounceFactor = 2.0F;
  m_system->addUpdater(m_floorUpdater);

  return true;
}

} // namespace particles::EFFECTS
