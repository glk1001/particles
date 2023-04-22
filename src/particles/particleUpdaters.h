#pragma once

#include "particles.h"

#include <vector>

namespace PARTICLES::UPDATERS
{

class EulerUpdater : public IParticleUpdater
{
public:
  explicit EulerUpdater(const glm::vec4& globalAcceleration) noexcept;

  auto update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_globalAcceleration;
};

// Collision with the floor :) todo: implement a collision model
class FloorUpdater : public IParticleUpdater
{
public:
  FloorUpdater(float floorY, float bounceFactor) noexcept;

  auto update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  float m_floorY;
  float m_bounceFactor;
};

class AttractorUpdater : public IParticleUpdater
{
public:
  AttractorUpdater() noexcept = default;

  auto add(const glm::vec4& attr) noexcept -> void;

  auto update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  std::vector<glm::vec4> m_attractors{}; // .w is force
};

inline auto AttractorUpdater::add(const glm::vec4& attr) noexcept -> void
{
  m_attractors.push_back(attr);
}

class BasicColorUpdater : public IParticleUpdater
{
public:
  auto update(double dt, ParticleData* particleData) noexcept -> void override;
};

class PosColorUpdater : public IParticleUpdater
{
public:
  PosColorUpdater(const glm::vec4& minPos, const glm::vec4& maxPos) noexcept;

  auto update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_minPos;
  glm::vec4 m_maxPos;
};

class VelColorUpdater : public IParticleUpdater
{
public:
  VelColorUpdater(const glm::vec4& minVel, const glm::vec4& maxVel) noexcept;

  auto update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_minVel;
  glm::vec4 m_maxVel;
};

class BasicTimeUpdater : public IParticleUpdater
{
public:
  auto update(double dt, ParticleData* particleData) noexcept -> void override;
};

} // namespace PARTICLES::UPDATERS
