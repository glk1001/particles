#pragma once

#include "effect.h"
#include "particles/particleGenerators.h"
#include "particles/particleUpdaters.h"
#include "particles/particles.h"

#include <memory>

namespace PARTICLES::EFFECTS
{

class TunnelEffect : public IEffect
{
public:
  [[nodiscard]] auto initialize(size_t numParticles) -> bool override;
  auto reset() -> void override;

  auto cpuUpdate(double dt) -> void override;

  [[nodiscard]] auto numAllParticles() -> size_t override;
  [[nodiscard]] auto numAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const PARTICLES::ParticleSystem* override;

private:
  std::shared_ptr<PARTICLES::ParticleSystem> m_system{};
  std::shared_ptr<PARTICLES::GENERATORS::RoundPosGen> m_posGenerator{};
  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGen> m_colGenerator{};
};

inline auto TunnelEffect::reset() -> void
{
  m_system->reset();
}

inline auto TunnelEffect::cpuUpdate(const double dt) -> void
{
  m_system->update(dt);
}

inline auto TunnelEffect::numAllParticles() -> size_t
{
  return m_system->numAllParticles();
}

inline auto TunnelEffect::numAliveParticles() -> size_t
{
  return m_system->numAliveParticles();
}

inline auto TunnelEffect::GetSystem() const -> const PARTICLES::ParticleSystem*
{
  return m_system.get();
}

} // namespace PARTICLES::EFFECTS
