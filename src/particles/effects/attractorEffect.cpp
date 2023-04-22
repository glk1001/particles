#include "attractorEffect.h"

#include "particles/particleGenerators.h"
#include "particles/particleUpdaters.h"

namespace PARTICLES::EFFECTS
{

using GENERATORS::BasicColorGen;
using GENERATORS::BasicTimeGen;
using GENERATORS::BoxPosGen;
using GENERATORS::SphereVelGen;
using UPDATERS::AttractorUpdater;
using UPDATERS::BasicTimeUpdater;
using UPDATERS::EulerUpdater;
using UPDATERS::VelColorUpdater;

auto AttractorEffect::initialize(const size_t numParticles) -> bool
{
  //
  // PARTICLES
  //
  const auto numParticlesToUse = 0 == numParticles ? 250000 : numParticles;
  m_system                     = std::make_shared<ParticleSystem>(numParticlesToUse);

  //
  // common
  //
  m_colGenerator = std::make_shared<BasicColorGen>(glm::vec4{0.99F, 0.99F, 0.99F, 1.00F},
                                                   glm::vec4{0.99F, 0.99F, 1.00F, 1.00F},
                                                   glm::vec4{0.99F, 0.99F, 0.99F, 0.00F},
                                                   glm::vec4{0.99F, 0.99F, 1.00F, 0.25F});

  auto velGenerator = std::make_shared<SphereVelGen>(0.1F, 0.1F);

  auto timeGenerator = std::make_shared<BasicTimeGen>(1.6F, 4.0F);

  //
  // emitter 1:
  //
  auto particleEmitter = std::make_shared<ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerators[0] = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, -0.25F, 0.0F},
                                                     glm::vec4{0.0F, 0.0F, +0.00F, 0.0F});
    particleEmitter->addGenerator(m_posGenerators[0]);

    particleEmitter->addGenerator(m_colGenerator);
    particleEmitter->addGenerator(velGenerator);
    particleEmitter->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter);

  //
  // emitter 2:
  //
  auto particleEmitter2 = std::make_shared<ParticleEmitter>();
  {
    particleEmitter2->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    m_posGenerators[1] = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, 0.25F, 0.0F},
                                                     glm::vec4{0.0F, 0.0F, 0.0F, 0.0F});
    particleEmitter2->addGenerator(m_posGenerators[1]);

    particleEmitter2->addGenerator(m_colGenerator);
    particleEmitter2->addGenerator(velGenerator);
    particleEmitter2->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter2);

  //
  // emitter 3:
  //
  auto particleEmitter3 = std::make_shared<ParticleEmitter>();
  {
    particleEmitter3->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    m_posGenerators[2] = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, 0.25F, 0.0F},
                                                     glm::vec4{0.0F, 0.0F, 0.0F, 0.0F});
    particleEmitter3->addGenerator(m_posGenerators[2]);

    particleEmitter3->addGenerator(m_colGenerator);
    particleEmitter3->addGenerator(velGenerator);
    particleEmitter3->addGenerator(timeGenerator);
  }
  m_system->addEmitter(particleEmitter3);

  //
  // updaters:
  //
  auto timeUpdater = std::make_shared<BasicTimeUpdater>();
  m_system->addUpdater(timeUpdater);

  auto colorUpdater = std::make_shared<VelColorUpdater>(glm::vec4{-0.5F, -0.5F, -0.5F, 0.0F},
                                                        glm::vec4{+2.0F, +2.0F, +2.0F, 2.0F});
  m_system->addUpdater(colorUpdater);

  m_attractors = std::make_shared<AttractorUpdater>();
  m_attractors->add(glm::vec4{+3.00F, +0.00F, +0.75F, 1.0F});
  m_attractors->add(glm::vec4{+0.00F, +1.00F, -0.75F, 1.0F});
  m_attractors->add(glm::vec4{-0.40F, +0.75F, +0.00F, 1.0F});
  m_attractors->add(glm::vec4{-2.00F, -0.75F, +0.00F, 1.0F});
  m_system->addUpdater(m_attractors);

  auto eulerUpdater = std::make_shared<EulerUpdater>(glm::vec4{0.0F, 0.0F, 0.0F, 0.0F});
  m_system->addUpdater(eulerUpdater);

  return true;
}

} // namespace PARTICLES::EFFECTS
