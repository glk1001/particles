#pragma once

#include "effect.h"
#include "particleGenerators.h"
#include "particleRenderer.h"
#include "particleUpdaters.h"
#include "particles.h"

#include <memory>

class TunnelEffect : public IEffect
{
public:
  [[nodiscard]] auto initialize(size_t numParticles) -> bool override;
  auto reset() -> void override { m_system->reset(); }

  auto cpuUpdate(double dt) -> void override;

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
  std::shared_ptr<particles::ParticleSystem> m_system{};
  std::shared_ptr<particles::generators::RoundPosGen> m_posGenerator{};
  std::shared_ptr<particles::generators::BasicColorGen> m_colGenerator{};
};
