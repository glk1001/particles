#pragma once

#include <cstddef>
#include <glm/vec4.hpp>

namespace PARTICLES
{
class ParticleSystem;
}

namespace PARTICLES::EFFECTS
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

  virtual auto Reset() -> void = 0;
  virtual auto SetTintColor(const glm::vec4& tintColor) noexcept -> void = 0;
  virtual auto SetEffectCentre(const glm::vec4& effectCentre) noexcept -> void = 0;

  virtual auto Update(double dt) -> void = 0;

  [[nodiscard]] virtual auto GetNumAllParticles() -> size_t                        = 0;
  [[nodiscard]] virtual auto GetNumAliveParticles() -> size_t                      = 0;
  [[nodiscard]] virtual auto GetSystem() const -> const PARTICLES::ParticleSystem* = 0;
};

} // namespace PARTICLES::EFFECTS
