module;

#include <glm/vec4.hpp>
#include <memory>

export module Particles.Effects.Tunnel;

import Particles.Effects.Effect;
import Particles.ParticleGenerators;
import Particles.ParticleUpdaters;
import Particles.Particles;

export namespace PARTICLES::EFFECTS
{

class TunnelEffect : public IEffect
{
public:
  explicit TunnelEffect(size_t numParticles) noexcept;

  auto Reset() noexcept -> void override;

  auto SetTintColor([[maybe_unused]] const glm::vec4& tintColor) noexcept -> void override {}

  auto SetTintMixAmount([[maybe_unused]] const float mixAmount) noexcept -> void override {}

  auto SetMaxNumAliveParticles([[maybe_unused]] const size_t maxNumAliveParticles) noexcept
      -> void override
  {
  }

  auto Update(double dt) noexcept -> void override;

  [[nodiscard]] auto GetNumAllParticles() const noexcept -> size_t override;
  [[nodiscard]] auto GetNumAliveParticles() const noexcept -> size_t override;
  [[nodiscard]] auto GetSystem() const noexcept -> const PARTICLES::ParticleSystem& override;

private:
  std::shared_ptr<ParticleSystem> m_system;
  std::shared_ptr<GENERATORS::RoundPositionGenerator> m_positionGenerator;
  std::shared_ptr<GENERATORS::BasicColorGenerator> m_colorGenerator;

  auto UpdateEffect(double dt) noexcept -> void;
};

} // namespace PARTICLES::EFFECTS

namespace PARTICLES::EFFECTS
{

inline auto TunnelEffect::Reset() noexcept -> void
{
  m_system->Reset();
}

inline auto TunnelEffect::Update(const double dt) noexcept -> void
{
  UpdateEffect(dt);
  m_system->Update(dt);
}

inline auto TunnelEffect::GetNumAllParticles() const noexcept -> size_t
{
  return m_system->GetNumAllParticles();
}

inline auto TunnelEffect::GetNumAliveParticles() const noexcept -> size_t
{
  return m_system->GetNumAliveParticles();
}

inline auto TunnelEffect::GetSystem() const noexcept -> const PARTICLES::ParticleSystem&
{
  return *m_system;
}

} // namespace PARTICLES::EFFECTS
