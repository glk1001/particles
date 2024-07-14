module;

#include <glm/common.hpp>
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

  auto Update(double dt, ParticleData& particleData) noexcept -> void override;

private:
  glm::vec4 m_globalAcceleration;
};

// Collision with the floor :) todo: implement a collision model
class FloorUpdater : public IParticleUpdater
{
public:
  FloorUpdater(float floorY, float bounceFactor) noexcept;

  auto Update(double dt, ParticleData& particleData) noexcept -> void override;

private:
  float m_floorY;
  float m_bounceFactor;
};

class AttractorUpdater : public IParticleUpdater
{
public:
  AttractorUpdater() noexcept = default;

  auto AddAttractorPosition(const glm::vec4& attractorPosition) noexcept -> void;

  auto Update(double dt, ParticleData& particleData) noexcept -> void override;

private:
  std::vector<glm::vec4> m_attractorPositions; // .w is force
};

class IColorUpdater : public IParticleUpdater
{
public:
  auto SetTintColor(const glm::vec4& tintColor) noexcept -> void;
  auto SetTintMixAmount(float mixAmount) noexcept -> void; // higher mix amount for more tint

protected:
  [[nodiscard]] auto GetMixedTintColor() const noexcept -> const glm::vec4&;

private:
  static constexpr auto ONE_VEC = glm::vec4{1.0F};
  glm::vec4 m_tintColor         = ONE_VEC;
  float m_mixAmount             = 0.0F;
  glm::vec4 m_mixedTintColor    = ONE_VEC;
};

class BasicColorUpdater : public IColorUpdater
{
public:
  auto Update(double dt, ParticleData& particleData) noexcept -> void override;
};

class PositionColorUpdater : public IColorUpdater
{
public:
  PositionColorUpdater(const glm::vec4& minPosition, const glm::vec4& maxPosition) noexcept;

  auto Update(double dt, ParticleData& particleData) noexcept -> void override;

private:
  glm::vec4 m_minPosition;
  glm::vec4 m_maxPosition;
  glm::vec4 m_diffMinMaxPosition = m_maxPosition - m_minPosition;
};

class VelocityColorUpdater : public IColorUpdater
{
public:
  VelocityColorUpdater(const glm::vec4& minVelocity, const glm::vec4& maxVelocity) noexcept;

  auto Update(double dt, ParticleData& particleData) noexcept -> void override;

private:
  glm::vec4 m_minVelocity;
  glm::vec4 m_maxVelocity;
  glm::vec4 m_diffMinMaxVelocity = m_maxVelocity - m_minVelocity;
};

class BasicTimeUpdater : public IParticleUpdater
{
public:
  auto Update(double dt, ParticleData& particleData) noexcept -> void override;
};

} // namespace PARTICLES::UPDATERS

namespace PARTICLES::UPDATERS
{

inline auto AttractorUpdater::AddAttractorPosition(const glm::vec4& attractorPosition) noexcept
    -> void
{
  m_attractorPositions.push_back(attractorPosition);
}

inline auto IColorUpdater::SetTintColor(const glm::vec4& tintColor) noexcept -> void
{
  m_tintColor = tintColor;

  m_mixedTintColor = glm::mix(m_tintColor, ONE_VEC, m_mixAmount);
}

inline auto IColorUpdater::SetTintMixAmount(const float mixAmount) noexcept -> void
{
  m_mixAmount = mixAmount;

  m_mixedTintColor = glm::mix(m_tintColor, ONE_VEC, m_mixAmount);
}

inline auto IColorUpdater::GetMixedTintColor() const noexcept -> const glm::vec4&
{
  return m_mixedTintColor;
}

} // namespace PARTICLES::UPDATERS
