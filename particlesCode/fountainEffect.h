#pragma once

#include "effect.h"
#include "particleGenerators.h"
#include "particleUpdaters.h"
#include "particles.h"

#include <memory>

namespace particles::EFFECTS
{

class FountainEffect : public IEffect
{
public:
  [[nodiscard]] auto initialize(size_t numParticles) -> bool override;
  auto reset() -> void override;

  auto cpuUpdate(double dt) -> void override;

  [[nodiscard]] auto numAllParticles() -> size_t override;
  [[nodiscard]] auto numAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const particles::ParticleSystem* override;

private:
  std::shared_ptr<particles::ParticleSystem> m_system{};
  std::shared_ptr<particles::generators::BoxPosGen> m_posGenerator{};
  std::shared_ptr<particles::generators::BasicColorGen> m_colGenerator{};
  std::shared_ptr<particles::updaters::EulerUpdater> m_eulerUpdater{};
  std::shared_ptr<particles::updaters::FloorUpdater> m_floorUpdater{};
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

inline auto FountainEffect::GetSystem() const -> const particles::ParticleSystem*
{
  return m_system.get();
}

} // namespace particles::EFFECTS
