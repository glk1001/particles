#include "glParticleRenderer.h"
#include "particles.h"

namespace particles
{

auto GLParticleRenderer::generate(ParticleSystem* sys, [[maybe_unused]] bool useQuads) -> void
{
  assert(sys != nullptr);

  m_system = sys;
}

auto GLParticleRenderer::update() -> void
{
}

auto GLParticleRenderer::render() -> void
{
}

} // namespace particles
