#pragma once

#include "particles.h"

#include <vector>

namespace particles::updaters
{

class EulerUpdater : public particles::ParticleUpdater
{
public:
  glm::vec4 m_globalAcceleration{0.0};

public:
  auto update(double dt, ParticleData* p) -> void override;
};

// collision with the floor :) todo: implement a collision model
class FloorUpdater : public particles::ParticleUpdater
{
public:
  float m_floorY = 0.0F;
  float m_bounceFactor = 0.5F;

public:
  auto update(double dt, ParticleData* p) -> void override;
};

class AttractorUpdater : public particles::ParticleUpdater
{
public:
  auto update(double dt, ParticleData* p) -> void override;

  [[nodiscard]] auto collectionSize() const -> size_t { return m_attractors.size(); }
  auto add(const glm::vec4& attr) -> void { m_attractors.push_back(attr); }
  [[nodiscard]] auto get(const size_t id) -> glm::vec4& { return m_attractors[id]; }

protected:
  std::vector<glm::vec4> m_attractors; // .w is force
};

class BasicColorUpdater : public ParticleUpdater
{
public:
  auto update(double dt, ParticleData* p) -> void override;
};

class PosColorUpdater : public ParticleUpdater
{
public:
  glm::vec4 m_minPos{0.0};
  glm::vec4 m_maxPos{1.0};

public:
  auto update(double dt, ParticleData* p) -> void override;
};

class VelColorUpdater : public ParticleUpdater
{
public:
  glm::vec4 m_minVel{0.0};
  glm::vec4 m_maxVel{1.0};

public:
  auto update(double dt, ParticleData* p) -> void override;
};

class BasicTimeUpdater : public ParticleUpdater
{
public:
  auto update(double dt, ParticleData* p) -> void override;
};

} // namespace particles::updaters
