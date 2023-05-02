#pragma once

#include "particles/effects/effect.h"
#include "particles/particle_generators.h"
#include "particles/particle_updaters.h"
#include "particles/particles.h"

#include <memory>

namespace PARTICLES::EFFECTS
{

class FountainEffect : public IEffect
{
public:
  explicit FountainEffect(size_t numParticles) noexcept;

  auto Reset() -> void override;

  auto Update(double dt) -> void override;

  [[nodiscard]] auto GetNumAllParticles() -> size_t override;
  [[nodiscard]] auto GetNumAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const PARTICLES::ParticleSystem* override;

private:
  std::shared_ptr<PARTICLES::ParticleSystem> m_system{};
  std::shared_ptr<PARTICLES::GENERATORS::BoxPositionGenerator> m_positionGenerator{};
  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGenerator> m_colorGenerator{};
  std::shared_ptr<PARTICLES::UPDATERS::EulerUpdater> m_eulerUpdater{};
  std::shared_ptr<PARTICLES::UPDATERS::FloorUpdater> m_floorUpdater{};
  static constexpr auto FLOOR_Y = -0.25F;

  auto UpdateEffect(double dt) noexcept -> void;
};

inline auto FountainEffect::Reset() -> void
{
  m_system->Reset();
}

inline auto FountainEffect::Update(const double dt) -> void
{
  UpdateEffect(dt);
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
