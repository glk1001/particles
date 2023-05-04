#include "particles/effects/attractor_effect.h"

#include "particles/particle_generators.h"
#include "particles/particle_updaters.h"

#include <cmath>

namespace PARTICLES::EFFECTS
{

using GENERATORS::BasicColorGenerator;
using GENERATORS::BasicTimeGenerator;
using GENERATORS::BoxPositionGenerator;
using GENERATORS::SphereVelocityGenerator;
using UPDATERS::AttractorUpdater;
using UPDATERS::BasicTimeUpdater;
using UPDATERS::EulerUpdater;
using UPDATERS::VelocityColorUpdater;

AttractorEffect::AttractorEffect(const size_t numParticles) noexcept
{
  //
  // Particles
  //
  const auto numParticlesToUse = 0 == numParticles ? 250000 : numParticles;
  m_system                     = std::make_shared<ParticleSystem>(numParticlesToUse);

  //
  // common
  //
  static constexpr auto MIN_START_COLOR = glm::vec4{0.39F, 0.39F, 0.39F, 1.00F};
  static constexpr auto MAX_START_COLOR = glm::vec4{0.69F, 0.69F, 0.69F, 1.00F};
  static constexpr auto MIN_END_COLOR   = glm::vec4{0.09F, 0.09F, 0.09F, 0.00F};
  static constexpr auto MAX_END_COLOR   = glm::vec4{0.39F, 0.39F, 0.39F, 0.25F};
  m_colorGenerator                      = std::make_shared<BasicColorGenerator>(
      MIN_START_COLOR, MAX_START_COLOR, MIN_END_COLOR, MAX_END_COLOR);

  static constexpr auto MIN_SPHERE_VELOCITY = 0.1F;
  static constexpr auto MAX_SPHERE_VELOCITY = 0.1F;
  const auto velocityGenerator =
      std::make_shared<SphereVelocityGenerator>(MIN_SPHERE_VELOCITY, MAX_SPHERE_VELOCITY);

  static constexpr auto MIN_LIFETIME = 1.6F;
  static constexpr auto MAX_LIFETIME = 114.0F;
  const auto timeGenerator = std::make_shared<BasicTimeGenerator>(MIN_LIFETIME, MAX_LIFETIME);

  static constexpr auto EMIT_RATE_FACTOR = 0.1F;
  //
  // emitter 1:
  //
  const auto particleEmitter1 = std::make_shared<ParticleEmitter>();
  particleEmitter1->SetEmitRate(EMIT_RATE_FACTOR * static_cast<float>(numParticlesToUse));
  particleEmitter1->SetMaxNumAliveParticles(100000U);

  // pos:
  static constexpr auto GEN_POS1              = glm::vec4{0.0F, 0.0F, Z_GEN_POS1, 0.0F};
  static constexpr auto MAX_START_POS_OFFSET1 = glm::vec4{0.0F, 0.0F, 0.00F, 0.0F};
  m_positionGenerators[0] = std::make_shared<BoxPositionGenerator>(GEN_POS1, MAX_START_POS_OFFSET1);
  particleEmitter1->AddGenerator(m_positionGenerators[0]);

  particleEmitter1->AddGenerator(m_colorGenerator);
  particleEmitter1->AddGenerator(velocityGenerator);
  particleEmitter1->AddGenerator(timeGenerator);
  m_system->AddEmitter(particleEmitter1);

  //
  // emitter 2:
  //
  const auto particleEmitter2 = std::make_shared<ParticleEmitter>();
  particleEmitter2->SetEmitRate(EMIT_RATE_FACTOR * static_cast<float>(numParticlesToUse));
  particleEmitter2->SetMaxNumAliveParticles(100000U);

  static constexpr auto GEN_POS2              = glm::vec4{0.0F, 0.0F, Z_GEN_POS2, 0.0F};
  static constexpr auto MAX_START_POS_OFFSET2 = glm::vec4{0.0F, 0.0F, 0.00F, 0.0F};
  m_positionGenerators[1] = std::make_shared<BoxPositionGenerator>(GEN_POS2, MAX_START_POS_OFFSET2);
  particleEmitter2->AddGenerator(m_positionGenerators[1]);

  particleEmitter2->AddGenerator(m_colorGenerator);
  particleEmitter2->AddGenerator(velocityGenerator);
  particleEmitter2->AddGenerator(timeGenerator);
  m_system->AddEmitter(particleEmitter2);

  //
  // emitter 3:
  //
  const auto particleEmitter3 = std::make_shared<ParticleEmitter>();
  particleEmitter3->SetEmitRate(EMIT_RATE_FACTOR * static_cast<float>(numParticlesToUse));
  particleEmitter3->SetMaxNumAliveParticles(100000U);

  static constexpr auto GEN_POS3              = glm::vec4{0.0F, 0.0F, Z_GEN_POS3, 0.0F};
  static constexpr auto MAX_START_POS_OFFSET3 = glm::vec4{0.0F, 0.0F, 0.00F, 0.0F};
  m_positionGenerators[2] = std::make_shared<BoxPositionGenerator>(GEN_POS3, MAX_START_POS_OFFSET3);
  particleEmitter3->AddGenerator(m_positionGenerators[2]);

  particleEmitter3->AddGenerator(m_colorGenerator);
  particleEmitter3->AddGenerator(velocityGenerator);
  particleEmitter3->AddGenerator(timeGenerator);
  m_system->AddEmitter(particleEmitter3);

  //
  // updaters:
  //
  const auto timeUpdater = std::make_shared<BasicTimeUpdater>();
  m_system->AddUpdater(timeUpdater);

  static constexpr auto MIN_VELOCITY = glm::vec4{-0.5F, -0.5F, -0.5F, 0.0F};
  static constexpr auto MAX_VELOCITY = glm::vec4{+2.0F, +2.0F, +2.0F, 2.0F};
  m_colorUpdater = std::make_shared<VelocityColorUpdater>(MIN_VELOCITY, MAX_VELOCITY);
  m_system->AddUpdater(m_colorUpdater);

  static constexpr auto ATTRACTOR_POSITION1 = glm::vec4{0.0F, +0.00F, +0.75F, 1.0F};
  static constexpr auto ATTRACTOR_POSITION2 = glm::vec4{0.0F, +0.00F, -0.75F, 1.0F};
  static constexpr auto ATTRACTOR_POSITION3 = glm::vec4{0.0F, +0.75F, +0.00F, 1.0F};
  static constexpr auto ATTRACTOR_POSITION4 = glm::vec4{0.0F, -0.75F, +0.00F, 1.0F};
  m_attractorUpdater                        = std::make_shared<AttractorUpdater>();
  m_attractorUpdater->AddAttractorPosition(ATTRACTOR_POSITION1);
  m_attractorUpdater->AddAttractorPosition(ATTRACTOR_POSITION2);
  m_attractorUpdater->AddAttractorPosition(ATTRACTOR_POSITION3);
  m_attractorUpdater->AddAttractorPosition(ATTRACTOR_POSITION4);
  m_system->AddUpdater(m_attractorUpdater);

  static constexpr auto EULER_ACCELERATION = glm::vec4{0.0F, 0.0F, 0.0F, 0.0F};
  const auto eulerUpdater                  = std::make_shared<EulerUpdater>(EULER_ACCELERATION);
  m_system->AddUpdater(eulerUpdater);
}

auto AttractorEffect::UpdateEffect(const double dt) -> void
{
  static auto s_lifetime = 0.0F;
  s_lifetime += static_cast<float>(dt);

  static constexpr auto RADIUS = 0.55F;

  const auto m_zScale = 1.0F;

  static constexpr auto LIFETIME_FACTOR1 = 2.5F;
  m_positionGenerators[0]->SetPosition(
      {m_effectCentre.x + RADIUS * std::sin(s_lifetime * LIFETIME_FACTOR1),
       m_effectCentre.y + RADIUS * std::cos(s_lifetime * LIFETIME_FACTOR1),
       m_effectCentre.z + m_zScale * Z_GEN_POS1 * std::cos(s_lifetime * LIFETIME_FACTOR1),
       0.0F});

  static constexpr auto LIFETIME_FACTOR2 = 2.0F;
  m_positionGenerators[1]->SetPosition(
      {m_effectCentre.x - RADIUS * std::sin(s_lifetime * LIFETIME_FACTOR2),
       m_effectCentre.y + RADIUS * std::cos(s_lifetime * LIFETIME_FACTOR2),
       m_effectCentre.z + m_zScale * Z_GEN_POS2 * std::cos(s_lifetime * LIFETIME_FACTOR2),
       0.0F});

  static constexpr auto LIFETIME_FACTOR3 = 10.5F;
  m_positionGenerators[2]->SetPosition(
      {m_effectCentre.x - RADIUS * std::sin(s_lifetime * LIFETIME_FACTOR3),
       m_effectCentre.y + RADIUS * std::cos(s_lifetime * LIFETIME_FACTOR3),
       m_effectCentre.z + m_zScale * Z_GEN_POS3 * std::cos(s_lifetime * LIFETIME_FACTOR3),
       0.0F});
}

} // namespace PARTICLES::EFFECTS
