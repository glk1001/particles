#pragma once

#include <cstddef>

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

  // Creates the effect with desired number of PARTICLES, (0 means default for the effect).
  virtual auto initialize(size_t numParticles) -> bool = 0;
  virtual auto reset() -> void                         = 0;

  virtual auto cpuUpdate(double dt) -> void = 0;

  [[nodiscard]] virtual auto numAllParticles() -> size_t                           = 0;
  [[nodiscard]] virtual auto numAliveParticles() -> size_t                         = 0;
  [[nodiscard]] virtual auto GetSystem() const -> const PARTICLES::ParticleSystem* = 0;
};

} // namespace PARTICLES::EFFECTS
