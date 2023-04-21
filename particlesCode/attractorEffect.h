#pragma once

#include "effect.h"
#include "particleGenerators.h"
#include "particleUpdaters.h"
#include "particles.h"

#include <array>
#include <memory>

namespace particles::EFFECTS
{

class AttractorEffect : public IEffect
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
  static constexpr auto NUM_BOX_POS_GENERATORS = 3U;
  std::array<std::shared_ptr<particles::generators::BoxPosGen>, NUM_BOX_POS_GENERATORS>
      m_posGenerators{};
  std::shared_ptr<particles::generators::BasicColorGen> m_colGenerator{};
  std::shared_ptr<particles::updaters::AttractorUpdater> m_attractors{};
};

inline auto AttractorEffect::reset() -> void
{
  m_system->reset();
}

inline auto AttractorEffect::cpuUpdate(const double dt) -> void
{
  m_system->update(dt);
}

inline auto AttractorEffect::numAllParticles() -> size_t
{
  return m_system->numAllParticles();
}

inline auto AttractorEffect::numAliveParticles() -> size_t
{
  return m_system->numAliveParticles();
}

inline auto AttractorEffect::GetSystem() const -> const particles::ParticleSystem*
{
  return m_system.get();
}

} // namespace particles::EFFECTS
