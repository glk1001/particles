#include "tunnel_effect.h"

#include "particles/particle_generators.h"
#include "particles/particle_updaters.h"

#include <cmath>

namespace PARTICLES::EFFECTS
{

using GENERATORS::BasicColorGen;
using GENERATORS::BasicTimeGen;
using GENERATORS::BasicVelGen;
using GENERATORS::RoundPosGen;
using UPDATERS::BasicColorUpdater;
using UPDATERS::BasicTimeUpdater;
using UPDATERS::EulerUpdater;

auto TunnelEffect::Initialize(const size_t numParticles) -> bool
{
  //
  // Particles
  //
  const auto numParticlesToUse = 0 == numParticles ? 10000 : numParticles;
  m_system                     = std::make_shared<ParticleSystem>(numParticlesToUse);

  //
  // emitter:
  //
  const auto particleEmitter = std::make_shared<ParticleEmitter>();
  {
    particleEmitter->SetEmitRate(0.45F * static_cast<float>(numParticlesToUse));

    // pos:
    m_posGenerator = std::make_shared<RoundPosGen>(glm::vec4{0.0, 0.0, 0.0, 0.0}, 0.15F, 0.15F);
    particleEmitter->AddGenerator(m_posGenerator);

    m_colGenerator = std::make_shared<BasicColorGen>(glm::vec4{0.7, 0.0, 0.7, 1.0},
                                                     glm::vec4{1.0, 1.0, 1.0, 1.0},
                                                     glm::vec4{0.5, 0.0, 0.6, 0.0},
                                                     glm::vec4{0.7, 0.5, 1.0, 0.0});
    particleEmitter->AddGenerator(m_colGenerator);

    const auto velGenerator = std::make_shared<BasicVelGen>(glm::vec4{0.0F, 0.0F, 0.15F, 0.0F},
                                                            glm::vec4{0.0F, 0.0F, 0.45F, 0.0F});
    particleEmitter->AddGenerator(velGenerator);

    const auto timeGenerator = std::make_shared<BasicTimeGen>(1.0, 3.5);
    particleEmitter->AddGenerator(timeGenerator);
  }
  m_system->AddEmitter(particleEmitter);

  const auto timeUpdater = std::make_shared<BasicTimeUpdater>();
  m_system->AddUpdater(timeUpdater);

  const auto colorUpdater = std::make_shared<BasicColorUpdater>();
  //colorUpdater->m_minPos = glm::vec4{ -1.0f };
  //colorUpdater->m_maxPos = glm::vec4{ +1.0f };
  m_system->AddUpdater(colorUpdater);

  const auto eulerUpdater = std::make_shared<EulerUpdater>(glm::vec4{0.0, 0.0, 0.0, 0.0});
  m_system->AddUpdater(eulerUpdater);

  return true;
}

auto TunnelEffect::Update(const double dt) noexcept -> void
{
  static auto time = 0.0F;
  time += static_cast<float>(dt);

  m_posGenerator->SetCentreAndRadius(
      {0.1F * std::sin(time * 2.5F), 0.1F * std::cos(time * 2.5F), 0.0F, 0.0F},
      0.15F + (0.05F * std::sin(time)),
      0.15F + (0.05F * (std::sin(time) * std::cos(time * 0.5F))));
//      0.15F + (0.01F * std::sin(time)),
//      0.15F + (0.01F * std::cos(time)));
}

} // namespace PARTICLES::EFFECTS
