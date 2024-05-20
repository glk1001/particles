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

  auto Reset() -> void override;

  auto SetTintColor([[maybe_unused]] const glm::vec4& tintColor) noexcept -> void override
  {
  }

  auto SetTintMixAmount([[maybe_unused]] const float mixAmount) noexcept -> void override
  {
  }

  auto SetMaxNumAliveParticles([[maybe_unused]] const size_t maxNumAliveParticles) noexcept
    -> void override
  {
  }

  auto Update(double dt) -> void override;

  [[nodiscard]] auto GetNumAllParticles() -> size_t override;
  [[nodiscard]] auto GetNumAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const PARTICLES::ParticleSystem* override;

private:
  std::shared_ptr<PARTICLES::ParticleSystem> m_system{};
  std::shared_ptr<PARTICLES::GENERATORS::RoundPositionGenerator> m_positionGenerator{};
  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGenerator> m_colorGenerator{};

  auto UpdateEffect(double dt) noexcept -> void;
};

} // namespace PARTICLES::EFFECTS

namespace PARTICLES::EFFECTS
{

inline auto TunnelEffect::Reset() -> void
{
  m_system->Reset();
}

inline auto TunnelEffect::Update(const double dt) -> void
{
  UpdateEffect(dt);
  m_system->Update(dt);
}

inline auto TunnelEffect::GetNumAllParticles() -> size_t
{
  return m_system->GetNumAllParticles();
}

inline auto TunnelEffect::GetNumAliveParticles() -> size_t
{
  return m_system->GetNumAliveParticles();
}

inline auto TunnelEffect::GetSystem() const -> const PARTICLES::ParticleSystem*
{
  return m_system.get();
}

} // namespace PARTICLES::EFFECTS
