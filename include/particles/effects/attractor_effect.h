#pragma once

#include "particles/effects/effect.h"
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
  explicit AttractorEffect(size_t numParticles) noexcept;

  auto AddUpdater(const std::shared_ptr<IParticleUpdater>& updater) noexcept -> void;

  auto Reset() -> void override;

  auto Update(double dt) -> void override;

  [[nodiscard]] auto GetNumAllParticles() -> size_t override;
  [[nodiscard]] auto GetNumAliveParticles() -> size_t override;
  [[nodiscard]] auto GetSystem() const -> const PARTICLES::ParticleSystem* override;

private:
  std::shared_ptr<PARTICLES::ParticleSystem> m_system{};

  static constexpr auto NUM_BOX_POS_GENERATORS = 3U;
  std::array<std::shared_ptr<PARTICLES::GENERATORS::BoxPositionGenerator>, NUM_BOX_POS_GENERATORS>
      m_positionGenerators{};
  static constexpr auto Z_GEN_POS1 = -0.25F;
  static constexpr auto Z_GEN_POS2 = +0.25F;
  static constexpr auto Z_GEN_POS3 = +0.25F;

  std::shared_ptr<PARTICLES::GENERATORS::BasicColorGenerator> m_colorGenerator{};
  std::shared_ptr<PARTICLES::UPDATERS::AttractorUpdater> m_attractorUpdater{};

  auto UpdateEffect(double dt) -> void;
};

inline auto AttractorEffect::Reset() -> void
{
  m_system->Reset();
}

inline auto AttractorEffect::AddUpdater(const std::shared_ptr<IParticleUpdater>& updater) noexcept
    -> void
{
  m_system->AddUpdater(updater);
}

inline auto AttractorEffect::Update(const double dt) -> void
{
  UpdateEffect(dt);
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
