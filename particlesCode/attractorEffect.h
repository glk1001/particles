#pragma once

#include "effect.h"
#include "particleGenerators.h"
#include "particleRenderer.h"
#include "particleUpdaters.h"
#include "particles.h"

#include <array>
#include <memory>

class AttractorEffect : public IEffect
{
public:
  [[nodiscard]] auto initialize(size_t numParticles) -> bool override;
  [[nodiscard]] auto initializeRenderer() -> bool override;
  auto reset() -> void override { m_system->reset(); }
  auto clean() -> void override;

  auto update(double dt) -> void override;
  auto cpuUpdate(double dt) -> void override;
  auto gpuUpdate(double dt) -> void override;
  auto render() -> void override;

  [[nodiscard]] auto numAllParticles() -> size_t override { return m_system->numAllParticles(); }
  [[nodiscard]] auto numAliveParticles() -> size_t override
  {
    return m_system->numAliveParticles();
  }
  [[nodiscard]] auto GetSystem() const -> const particles::ParticleSystem* override
  {
    return m_system.get();
  }

private:
  std::shared_ptr<particles::ParticleSystem> m_system;
  std::shared_ptr<particles::IParticleRenderer> m_renderer;
  static constexpr auto NUM_BOX_POS_GENERATORS = 3U;
  std::array<std::shared_ptr<particles::generators::BoxPosGen>, NUM_BOX_POS_GENERATORS>
      m_posGenerators{};
  std::shared_ptr<particles::generators::BasicColorGen> m_colGenerator;
  std::shared_ptr<particles::updaters::AttractorUpdater> m_attractors;
  float m_zScale;
};
