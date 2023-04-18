#include "particleRenderer.h"

#include "glParticleRenderer.h"

#include <string>

namespace particles
{

std::shared_ptr<IParticleRenderer> RendererFactory::create(const char* const name)
{
  if (const auto renderer = std::string{name}; "gl" == renderer)
  {
    return std::make_shared<GLParticleRenderer>();
  }

  return nullptr;
}

} // namespace particles
