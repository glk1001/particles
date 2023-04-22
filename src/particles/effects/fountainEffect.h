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
  [[nodiscard]] auto Initialize(size_t numParticles) -> bool override;
  auto Reset() -> void override;

  auto CpuUpdate(double dt) -> void override;

  [[nodiscard]] auto GetNumAllParticles() -> size_t override;
  [[nodiscard]] auto GetNumAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const PARTICLES::ParticleSystem* override;

private:
  std::shared_ptr<PARTICLES::ParticleSystem> m_system{};
  std::shared_ptr<PARTICLES::GENERATORS::BoxPosGen> m_posGenerator{};
  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGen> m_colGenerator{};
  std::shared_ptr<PARTICLES::UPDATERS::EulerUpdater> m_eulerUpdater{};
  std::shared_ptr<PARTICLES::UPDATERS::FloorUpdater> m_floorUpdater{};
};

inline auto FountainEffect::Reset() -> void
{
  m_system->Reset();
}

inline auto FountainEffect::CpuUpdate(const double dt) -> void
{
  m_system->Update(dt);
}

inline auto FountainEffect::GetNumAllParticles() -> size_t
{
  return m_system->GetNumAllParticles();
}

inline auto FountainEffect::GetNumAliveParticles() -> size_t
{
  return m_system->GetNumAliveParticles();
}

inline auto FountainEffect::GetSystem() const -> const PARTICLES::ParticleSystem*
{
  return m_system.get();
}

} // namespace PARTICLES::EFFECTS
