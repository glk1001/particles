#include "attractor_effect.h"

#include "particles/particle_generators.h"
#include "particles/particle_updaters.h"

#include <cmath>

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

auto AttractorEffect::Initialize(const size_t numParticles) -> bool
{
  //
  // Particles
  //
  const auto numParticlesToUse = 0 == numParticles ? 250000 : numParticles;
  m_system                     = std::make_shared<ParticleSystem>(numParticlesToUse);

  //
  // common
  //
  m_colGenerator = std::make_shared<BasicColorGen>(glm::vec4{0.39F, 0.39F, 0.39F, 1.00F},
                                                   glm::vec4{0.69F, 0.69F, 0.69F, 1.00F},
                                                   glm::vec4{0.09F, 0.09F, 0.09F, 0.00F},
                                                   glm::vec4{0.39F, 0.39F, 0.39F, 0.25F});

  const auto velGenerator = std::make_shared<SphereVelGen>(0.1F, 0.1F);

  const auto timeGenerator = std::make_shared<BasicTimeGen>(1.6F, 4.0F);

  //
  // emitter 1:
  //
  const auto particleEmitter = std::make_shared<ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerators[0] = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, -0.25F, 0.0F},
                                                     glm::vec4{0.0F, 0.0F, +0.00F, 0.0F});
    particleEmitter->AddGenerator(m_posGenerators[0]);

    particleEmitter->AddGenerator(m_colGenerator);
    particleEmitter->AddGenerator(velGenerator);
    particleEmitter->AddGenerator(timeGenerator);
  }
  m_system->AddEmitter(particleEmitter);

  //
  // emitter 2:
  //
  const auto particleEmitter2 = std::make_shared<ParticleEmitter>();
  {
    particleEmitter2->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    m_posGenerators[1] = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, 0.25F, 0.0F},
                                                     glm::vec4{0.0F, 0.0F, 0.00F, 0.0F});
    particleEmitter2->AddGenerator(m_posGenerators[1]);

    particleEmitter2->AddGenerator(m_colGenerator);
    particleEmitter2->AddGenerator(velGenerator);
    particleEmitter2->AddGenerator(timeGenerator);
  }
  m_system->AddEmitter(particleEmitter2);

  //
  // emitter 3:
  //
  const auto particleEmitter3 = std::make_shared<ParticleEmitter>();
  {
    particleEmitter3->SetEmitRate(0.1F * static_cast<float>(numParticlesToUse));

    m_posGenerators[2] = std::make_shared<BoxPosGen>(glm::vec4{0.0F, 0.0F, 0.25F, 0.0F},
                                                     glm::vec4{0.0F, 0.0F, 0.0F, 0.0F});
    particleEmitter3->AddGenerator(m_posGenerators[2]);

    particleEmitter3->AddGenerator(m_colGenerator);
    particleEmitter3->AddGenerator(velGenerator);
    particleEmitter3->AddGenerator(timeGenerator);
  }
  m_system->AddEmitter(particleEmitter3);

  //
  // updaters:
  //
  const auto timeUpdater = std::make_shared<BasicTimeUpdater>();
  m_system->AddUpdater(timeUpdater);

  const auto colorUpdater = std::make_shared<VelColorUpdater>(glm::vec4{-0.5F, -0.5F, -0.5F, 0.0F},
                                                              glm::vec4{+2.0F, +2.0F, +2.0F, 2.0F});
  m_system->AddUpdater(colorUpdater);

  m_attractors = std::make_shared<AttractorUpdater>();
  m_attractors->Add(glm::vec4{0.0F, +0.00F, +0.75F, 1.0F});
  m_attractors->Add(glm::vec4{0.0F, +0.00F, -0.75F, 1.0F});
  m_attractors->Add(glm::vec4{0.0F, +0.75F, +0.00F, 1.0F});
  m_attractors->Add(glm::vec4{0.0F, -0.75F, +0.00F, 1.0F});
//  m_attractors->Add(glm::vec4{+0.75F, 0.0F, +0.00F, 1.0F});
//  m_attractors->Add(glm::vec4{-0.75F, 0.0F, +0.00F, 1.0F});
  m_system->AddUpdater(m_attractors);

  const auto eulerUpdater = std::make_shared<EulerUpdater>(glm::vec4{0.0F, 0.0F, 0.0F, 0.0F});
  m_system->AddUpdater(eulerUpdater);

  return true;
}

auto AttractorEffect::Update(const double dt) -> void
{
  static auto time = 0.0F;
  time += static_cast<float>(dt);

  static constexpr auto r = 0.55F;

  const auto m_zScale = 1.0F;

  m_posGenerators[0]->SetPosition({+r * std::sin(time * 2.5F),
                                   +r * std::cos(time * 2.5F),
                                   -m_zScale * 0.25F * std::cos(time * 2.5F),
                                   0.0F});

  m_posGenerators[1]->SetPosition({-r * std::sin(time * 2.0F),
                                   +r * std::cos(time * 2.0F),
                                   m_zScale * 0.25F * std::cos(time * 2.0F),
                                   0.0F});

  m_posGenerators[2]->SetPosition({-r * std::sin(time * 1.5F),
                                   +r * std::cos(time * 1.5F),
                                   m_zScale * 0.25F * std::cos(time * 1.5F),
                                   0.0F});
}

} // namespace PARTICLES::EFFECTS
