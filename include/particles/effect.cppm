module;

#include <cstddef>
#include <glm/vec4.hpp>

export module Particles.Effect;

import Particles.Particles;

export namespace PARTICLES::EFFECTS
{

class IEffect
{
public:
  IEffect()                                  = default;
  IEffect(const IEffect&)                    = delete;
  IEffect(IEffect&&)                         = delete;
  virtual ~IEffect()                         = default;
  auto operator=(const IEffect&) -> IEffect& = delete;
  auto operator=(IEffect&&) -> IEffect&      = delete;

  virtual auto Reset() noexcept -> void = 0;

  virtual auto SetTintColor(const glm::vec4& tintColor) noexcept -> void = 0;
  virtual auto SetTintMixAmount(float mixAmount) noexcept -> void        = 0;
  // Higher mix amount for more tint.
  virtual auto SetMaxNumAliveParticles(size_t maxNumAliveParticles) noexcept -> void = 0;

  virtual auto Update(double dt) noexcept -> void = 0;

  [[nodiscard]] virtual auto GetSystem() const noexcept -> const PARTICLES::ParticleSystem& = 0;

  [[nodiscard]] auto GetNumAllParticles() const noexcept -> size_t;
  [[nodiscard]] auto GetNumAliveParticles() const noexcept -> size_t;
};

} // namespace PARTICLES::EFFECTS

namespace PARTICLES::EFFECTS
{

inline auto IEffect::GetNumAllParticles() const noexcept -> size_t
{
  return GetSystem().GetNumAllParticles();
}

inline auto IEffect::GetNumAliveParticles() const noexcept -> size_t
{
  return GetSystem().GetNumAliveParticles();
}

} // namespace PARTICLES::EFFECTS
