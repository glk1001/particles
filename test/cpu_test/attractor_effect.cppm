module;

#include <array>
#include <cstdlib>
#include <glm/fwd.hpp>
#include <memory>

export module CpuTest.Particles.AttractorEffect;

import Particles.Effect;
import Particles.ParticleGenerators;
import Particles.ParticleUpdaters;
import Particles.Particles;

using PARTICLES::GENERATORS::BasicColorGenerator;
using PARTICLES::GENERATORS::BoxPositionGenerator;
using PARTICLES::UPDATERS::AttractorUpdater;
using PARTICLES::UPDATERS::VelocityColorUpdater;

export namespace PARTICLES::EFFECTS
{

class AttractorEffect : public IEffect
{
public:
  static constexpr auto NUM_EMITTERS = 3U;

  explicit AttractorEffect(size_t numParticles) noexcept;

  auto Reset() noexcept -> void override;

  auto SetTintColor(const glm::vec4& tintColor) noexcept -> void override;
  auto SetTintMixAmount(float mixAmount) noexcept -> void override;
  auto SetMaxNumAliveParticles(size_t maxNumAliveParticles) noexcept -> void override;

  auto Update(double dt) noexcept -> void override;

  [[nodiscard]] auto GetSystem() const noexcept -> const ParticleSystem& override;

private:
  ParticleSystem m_system;

  std::shared_ptr<VelocityColorUpdater> m_colorUpdater;
  std::array<std::shared_ptr<ParticleEmitter>, NUM_EMITTERS> m_particleEmitters;
  std::array<std::shared_ptr<BoxPositionGenerator>, NUM_EMITTERS> m_positionGenerators;

  auto AddEmitters() noexcept -> void;
  auto AddUpdaters() noexcept -> void;

  auto UpdateEffect(double dt) noexcept -> void;
};

} // namespace PARTICLES::EFFECTS

namespace PARTICLES::EFFECTS
{

inline auto AttractorEffect::Reset() noexcept -> void
{
  m_system.Reset();
}

inline auto AttractorEffect::SetTintColor(const glm::vec4& tintColor) noexcept -> void
{
  m_colorUpdater->SetTintColor(tintColor);
}

inline auto AttractorEffect::SetTintMixAmount(const float mixAmount) noexcept -> void
{
  m_colorUpdater->SetTintMixAmount(mixAmount);
}

inline auto AttractorEffect::SetMaxNumAliveParticles(const size_t maxNumAliveParticles) noexcept
    -> void
{
  for (auto& particleEmitter : m_particleEmitters)
  {
    particleEmitter->SetMaxNumAliveParticles(maxNumAliveParticles);
  }
}

inline auto AttractorEffect::Update(const double dt) noexcept -> void
{
  UpdateEffect(dt);
  m_system.Update(dt);
}

inline auto AttractorEffect::GetSystem() const noexcept -> const ParticleSystem&
{
  return m_system;
}

} // namespace PARTICLES::EFFECTS
