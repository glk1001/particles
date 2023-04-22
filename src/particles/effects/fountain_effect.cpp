#include "fountain_effect.h"

#include "particles/particle_generators.h"
#include "particles/particle_updaters.h"

namespace PARTICLES::EFFECTS
{

using GENERATORS::BasicColorGen;
using GENERATORS::BasicTimeGen;
using GENERATORS::BasicVelGen;
using GENERATORS::BoxPosGen;
using UPDATERS::BasicColorUpdater;
using UPDATERS::BasicTimeUpdater;
using UPDATERS::EulerUpdater;
using UPDATERS::FloorUpdater;

auto FountainEffect::Initialize(const size_t numParticles) -> bool
{
  //
  // PARTICLES
  //
  const auto numParticlesToUse = 0 == numParticles ? 10000 : numParticles;
  m_system                     = std::make_shared<ParticleSystem>(numParticlesToUse);

  //
  // emitter:
  //
  const auto particleEmitter = std::make_shared<ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.25F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerator = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, 0.0F, 0.0F},
                                                 glm::vec4{0.1F, 0.F, 0.0F, 0.0F});
    particleEmitter->AddGenerator(m_posGenerator);

    m_colGenerator = std::make_shared<BasicColorGen>(glm::vec4{0.5F, 0.5F, 0.5F, 1.0F},
                                                     glm::vec4{1.0F, 1.0F, 1.0F, 1.0F},
                                                     glm::vec4{0.5F, 0.0F, 0.6F, 0.0F},
                                                     glm::vec4{0.7F, 0.5F, 1.0F, 0.0F});
    particleEmitter->AddGenerator(m_colGenerator);

    const auto velGenerator = std::make_shared<BasicVelGen>(glm::vec4{-0.5F, 0.052F, -0.05F, 0.0F},
                                                            glm::vec4{+0.5F, 0.250F, +0.05F, 0.0F});
    particleEmitter->AddGenerator(velGenerator);

    const auto timeGenerator = std::make_shared<BasicTimeGen>(30.0F, 40.0F);
    particleEmitter->AddGenerator(timeGenerator);
  }
  m_system->AddEmitter(particleEmitter);

  const auto timeUpdater = std::make_shared<BasicTimeUpdater>();
  m_system->AddUpdater(timeUpdater);

  const auto colorUpdater = std::make_shared<BasicColorUpdater>();
  //colorUpdater->m_minVel = glm::vec4{0.0F, 0.0F, -0.0F, 0.0F};
  //colorUpdater->m_maxVel = glm::vec4{0.5F, 1.0F, -0.0F, 0.0F};
  m_system->AddUpdater(colorUpdater);

  m_eulerUpdater = std::make_shared<EulerUpdater>(glm::vec4{0.0F, -2.0F, 0.0F, 0.0F});
  m_system->AddUpdater(m_eulerUpdater);

  m_floorUpdater = std::make_shared<FloorUpdater>(-3.50F, 2.0F);
  m_system->AddUpdater(m_floorUpdater);

  return true;
}

} // namespace PARTICLES::EFFECTS
