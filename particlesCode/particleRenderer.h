#pragma once

#include <memory>

namespace particles
{

class ParticleSystem;

class IParticleRenderer
{
public:
  IParticleRenderer()                                            = default;
  virtual ~IParticleRenderer()                                   = default;
  IParticleRenderer(const IParticleRenderer&)                    = delete;
  IParticleRenderer(IParticleRenderer&&)                         = delete;
  auto operator=(const IParticleRenderer&) -> IParticleRenderer& = delete;
  auto operator=(IParticleRenderer&&) -> IParticleRenderer&      = delete;

  virtual void generate(ParticleSystem* sys, bool useQuads) = 0;
  virtual void destroy()                                    = 0;
  virtual void update()                                     = 0;
  virtual void render()                                     = 0;
};

class RendererFactory
{
public:
  static std::shared_ptr<IParticleRenderer> create(const char* name);
};

} // namespace particles
