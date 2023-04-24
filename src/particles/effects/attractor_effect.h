#pragma once

#include "effect.h"
#include "particles/particle_generators.h"
#include "particles/particle_updaters.h"
#include "particles/particles.h"

#include <array>
#include <memory>

namespace PARTICLES::EFFECTS
{

class AttractorEffect : public IEffect
{
public:
  [[nodiscard]] auto Initialize(size_t numParticles) -> bool override;
  auto Reset() -> void override;

  auto CpuUpdate(double dt) -> void override;

  [[nodiscard]] auto GetNumAllParticles() -> size_t override;
  [[nodiscard]] auto GetNumAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const PARTICLES::ParticleSystem* override;

private:
  std::shared_ptr<PARTICLES::ParticleSystem> m_system{};
  static constexpr auto NUM_BOX_POS_GENERATORS = 3U;
  std::array<std::shared_ptr<PARTICLES::GENERATORS::BoxPosGen>, NUM_BOX_POS_GENERATORS>
      m_posGenerators{};
  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGen> m_colGenerator{};
  std::shared_ptr<PARTICLES::UPDATERS::AttractorUpdater> m_attractors{};

  auto Update(double dt) -> void;
};

inline auto AttractorEffect::Reset() -> void
{
  m_system->Reset();
}

inline auto AttractorEffect::CpuUpdate(const double dt) -> void
{
  Update(dt);
  m_system->Update(dt);
}

inline auto AttractorEffect::GetNumAllParticles() -> size_t
{
  return m_system->GetNumAllParticles();
}

inline auto AttractorEffect::GetNumAliveParticles() -> size_t
{
  return m_system->GetNumAliveParticles();
}

inline auto AttractorEffect::GetSystem() const -> const PARTICLES::ParticleSystem*
{
  return m_system.get();
}

} // namespace PARTICLES::EFFECTS
