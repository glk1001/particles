#pragma once

#include "particles.h"

#include <glm/vec4.hpp>
#include <vector>

namespace PARTICLES::UPDATERS
{

class EulerUpdater : public IParticleUpdater
{
public:
  explicit EulerUpdater(const glm::vec4& globalAcceleration) noexcept;

  auto Update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_globalAcceleration;
};

// Collision with the floor :) todo: implement a collision model
class FloorUpdater : public IParticleUpdater
{
public:
  FloorUpdater(float floorY, float bounceFactor) noexcept;

  auto Update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  float m_floorY;
  float m_bounceFactor;
};

class AttractorUpdater : public IParticleUpdater
{
public:
  AttractorUpdater() noexcept = default;

  auto AddAttractorPosition(const glm::vec4& attractorPosition) noexcept -> void;

  auto Update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  std::vector<glm::vec4> m_attractorPositions{}; // .w is force
};

class BasicColorUpdater : public IParticleUpdater
{
public:
  auto Update(double dt, ParticleData* particleData) noexcept -> void override;
};

class PositionColorUpdater : public IParticleUpdater
{
public:
  PositionColorUpdater(const glm::vec4& minPosition, const glm::vec4& maxPosition) noexcept;

  auto Update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_minPosition;
  glm::vec4 m_maxPosition;
};

class VelocityColorUpdater : public IParticleUpdater
{
public:
  VelocityColorUpdater(const glm::vec4& minVelocity, const glm::vec4& maxVelocity) noexcept;

  auto Update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_minVelocity;
  glm::vec4 m_maxVelocity;
};

class BasicTimeUpdater : public IParticleUpdater
{
public:
  auto Update(double dt, ParticleData* particleData) noexcept -> void override;
};

inline auto AttractorUpdater::AddAttractorPosition(const glm::vec4& attractorPosition) noexcept
    -> void
{
  m_attractorPositions.push_back(attractorPosition);
}

} // namespace PARTICLES::UPDATERS
