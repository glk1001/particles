#pragma once

#include "effect.h"
#include "particles/particleGenerators.h"
#include "particles/particleUpdaters.h"
#include "particles/particles.h"

#include <memory>

namespace PARTICLES::EFFECTS
{

class FountainEffect : public IEffect
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
  std::shared_ptr<PARTICLES::GENERATORS::BoxPosGen> m_posGenerator{};
  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGen> m_colGenerator{};
  std::shared_ptr<PARTICLES::UPDATERS::EulerUpdater> m_eulerUpdater{};
  std::shared_ptr<PARTICLES::UPDATERS::FloorUpdater> m_floorUpdater{};
};

inline auto FountainEffect::reset() -> void
{
  m_system->reset();
}

inline auto FountainEffect::cpuUpdate(const double dt) -> void
{
  m_system->update(dt);
}

inline auto FountainEffect::numAllParticles() -> size_t
{
  return m_system->numAllParticles();
}

inline auto FountainEffect::numAliveParticles() -> size_t
{
  return m_system->numAliveParticles();
}

inline auto FountainEffect::GetSystem() const -> const PARTICLES::ParticleSystem*
{
  return m_system.get();
}

} // namespace PARTICLES::EFFECTS
