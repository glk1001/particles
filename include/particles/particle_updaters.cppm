module;

#include <glm/vec4.hpp>
#include <vector>

export module Particles.ParticleUpdaters;

import Particles.Particles;

export namespace PARTICLES::UPDATERS
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
  glm::vec4 m_diffMinMaxPosition = m_maxPosition - m_minPosition;
};

class VelocityColorUpdater : public IParticleUpdater
{
public:
  VelocityColorUpdater(const glm::vec4& minVelocity, const glm::vec4& maxVelocity) noexcept;

  auto SetTintColor(const glm::vec4& tintColor) noexcept -> void;
  auto SetTintMixAmount(float mixAmount) noexcept -> void; // higher mix amount for more tint

  auto Update(double dt, ParticleData* particleData) noexcept -> void override;

private:
  glm::vec4 m_minVelocity;
  glm::vec4 m_maxVelocity;
  glm::vec4 m_diffMinMaxVelocity = m_maxVelocity - m_minVelocity;
  glm::vec4 m_tintColor{1.0F};
  float m_mixAmount = 0.0F;
};

class BasicTimeUpdater : public IParticleUpdater
{
public:
  auto Update(double dt, ParticleData* particleData) noexcept -> void override;
};

} // namespace PARTICLES::UPDATERS

namespace PARTICLES::UPDATERS
{

inline auto AttractorUpdater::AddAttractorPosition(const glm::vec4& attractorPosition) noexcept
    -> void
{
  m_attractorPositions.push_back(attractorPosition);
}

inline auto VelocityColorUpdater::SetTintColor(const glm::vec4& tintColor) noexcept -> void
{
  m_tintColor = tintColor;
}

inline auto VelocityColorUpdater::SetTintMixAmount(const float mixAmount) noexcept -> void
{
  m_mixAmount = mixAmount;
}

} // namespace PARTICLES::UPDATERS
