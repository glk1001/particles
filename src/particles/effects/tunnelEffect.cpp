#include "tunnelEffect.h"

#include "glm/glm.hpp"

namespace PARTICLES::EFFECTS
{

auto TunnelEffect::initialize(const size_t numParticles) -> bool
{
  //
  // PARTICLES
  //
  const auto numParticlesToUse = 0 == numParticles ? 10000 : numParticles;
  m_system                     = std::make_shared<PARTICLES::ParticleSystem>(numParticlesToUse);

  //
  // emitter:
  //
  auto particleEmitter = std::make_shared<PARTICLES::ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.45F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerator = std::make_shared<PARTICLES::GENERATORS::RoundPosGen>();
    m_posGenerator->SetCentre(glm::vec4{0.0, 0.0, 0.0, 0.0});
    m_posGenerator->SetRadius(0.15F, 0.15F);
    particleEmitter->addGenerator(m_posGenerator);

    m_colGenerator = std::make_shared<PARTICLES::GENERATORS::BasicColorGen>();
    m_colGenerator->SetMinMaxStartColors(glm::vec4{0.5, 0.0, 0.5, 1.0},
                                         glm::vec4{1.0, 1.0, 1.0, 1.0});
    m_colGenerator->SetMinMaxEndColors(glm::vec4{0.2, 0.0, 0.6, 0.0},
                                       glm::vec4{0.7, 0.5, 1.0, 0.0});
    particleEmitter->addGenerator(m_colGenerator);

    auto velGenerator = std::make_shared<PARTICLES::GENERATORS::BasicVelGen>();
    velGenerator->SetMinMaxVelocity(glm::vec4{0.0F, 0.0F, 0.15F, 0.0F},
                                    glm::vec4{0.0F, 0.0F, 0.45F, 0.0F});
    particleEmitter->addGenerator(velGenerator);

    auto timeGenerator = std::make_shared<PARTICLES::GENERATORS::BasicTimeGen>();
    timeGenerator->SetMinMaxTime(1.0, 10.0);
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  auto timeUpdater = std::make_shared<PARTICLES::UPDATERS::BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater = std::make_shared<PARTICLES::UPDATERS::BasicColorUpdater>();
  //colorUpdater->m_minPos = glm::vec4{ -1.0f };
  //colorUpdater->m_maxPos = glm::vec4{ 1.0f };
  m_system->addUpdater(colorUpdater);

  auto eulerUpdater = std::make_shared<PARTICLES::UPDATERS::EulerUpdater>();
  eulerUpdater->SetGlobalAcceleration(glm::vec4{0.0, 0.0, 0.0, 0.0});
  m_system->addUpdater(eulerUpdater);

  return true;
}

} // namespace PARTICLES::EFFECTS
