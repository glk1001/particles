#include "tunnelEffect.h"

#include "particles/particleGenerators.h"
#include "particles/particleUpdaters.h"

namespace PARTICLES::EFFECTS
{

using GENERATORS::BasicColorGen;
using GENERATORS::BasicTimeGen;
using GENERATORS::BasicVelGen;
using GENERATORS::RoundPosGen;
using UPDATERS::BasicColorUpdater;
using UPDATERS::BasicTimeUpdater;
using UPDATERS::EulerUpdater;

auto TunnelEffect::initialize(const size_t numParticles) -> bool
{
  //
  // PARTICLES
  //
  const auto numParticlesToUse = 0 == numParticles ? 10000 : numParticles;
  m_system                     = std::make_shared<ParticleSystem>(numParticlesToUse);

  //
  // emitter:
  //
  auto particleEmitter = std::make_shared<ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.45F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerator = std::make_shared<RoundPosGen>(glm::vec4{0.0, 0.0, 0.0, 0.0}, 0.15F, 0.15F);
    particleEmitter->addGenerator(m_posGenerator);

    m_colGenerator = std::make_shared<BasicColorGen>(glm::vec4{0.5, 0.0, 0.5, 1.0},
                                                     glm::vec4{1.0, 1.0, 1.0, 1.0},
                                                     glm::vec4{0.2, 0.0, 0.6, 0.0},
                                                     glm::vec4{0.7, 0.5, 1.0, 0.0});
    particleEmitter->addGenerator(m_colGenerator);

    auto velGenerator = std::make_shared<BasicVelGen>(glm::vec4{0.0F, 0.0F, 0.15F, 0.0F},
                                                      glm::vec4{0.0F, 0.0F, 0.45F, 0.0F});
    particleEmitter->addGenerator(velGenerator);

    auto timeGenerator = std::make_shared<BasicTimeGen>(1.0, 10.0);
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  auto timeUpdater = std::make_shared<BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater = std::make_shared<BasicColorUpdater>();
  //colorUpdater->m_minPos = glm::vec4{ -1.0f };
  //colorUpdater->m_maxPos = glm::vec4{ 1.0f };
  m_system->addUpdater(colorUpdater);

  auto eulerUpdater = std::make_shared<EulerUpdater>(glm::vec4{0.0, 0.0, 0.0, 0.0});
  m_system->addUpdater(eulerUpdater);

  return true;
}

} // namespace PARTICLES::EFFECTS
