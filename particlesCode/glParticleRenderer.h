#pragma once

#include "particleRenderer.h"

namespace particles
{

class GLParticleRenderer : public IParticleRenderer
{
public:
  auto generate(ParticleSystem* sys, bool useQuads) -> void override;
  auto destroy() -> void override{};
  auto update() -> void override;
  auto render() -> void override;

protected:
  ParticleSystem* m_system{nullptr};

  unsigned int m_bufPos{0};
  unsigned int m_bufCol{0};
  unsigned int m_vao{0};
};

} // namespace particles
