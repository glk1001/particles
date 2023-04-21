#pragma once

#include "particles.h"

#include <vector>

namespace particles::generators
{

class BoxPosGen : public ParticleGenerator
{
public:
  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;

  auto SetPosition(const glm::vec4& position) noexcept -> void;
  auto SetMaxStartPositionOffset(const glm::vec4& positionOffset) noexcept -> void;

private:
  glm::vec4 m_pos{0.0F};
  glm::vec4 m_maxStartPosOffset{0.0F};
};

inline auto BoxPosGen::SetPosition(const glm::vec4& position) noexcept -> void
{
  m_pos = position;
}

inline auto BoxPosGen::SetMaxStartPositionOffset(const glm::vec4& positionOffset) noexcept -> void
{
  m_maxStartPosOffset = positionOffset;
}

class RoundPosGen : public ParticleGenerator
{
public:
  RoundPosGen() = default;
  RoundPosGen(const glm::vec4& center, const double radX, const double radY)
    : m_center{center}, m_radX{static_cast<float>(radX)}, m_radY{static_cast<float>(radY)}
  {
  }

  auto SetCentre(const glm::vec4& centre) noexcept -> void;
  auto SetRadius(float xRadius, float yRadius) noexcept -> void;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;

private:
  glm::vec4 m_center{0.0F};
  float m_radX = 0.0F;
  float m_radY = 0.0F;
};

inline auto RoundPosGen::SetCentre(const glm::vec4& centre) noexcept -> void
{
  m_center = centre;
}

inline auto RoundPosGen::SetRadius(const float xRadius, const float yRadius) noexcept -> void
{
  m_radX = xRadius;
  m_radY = yRadius;
}

class BasicColorGen : public ParticleGenerator
{
public:
  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;

  auto SetMinMaxStartColors(const glm::vec4& minColor, const glm::vec4& maxColor) noexcept -> void;
  auto SetMinMaxEndColors(const glm::vec4& minColor, const glm::vec4& maxColor) noexcept -> void;

private:
  glm::vec4 m_minStartCol{0.0F};
  glm::vec4 m_maxStartCol{0.0F};
  glm::vec4 m_minEndCol{0.0F};
  glm::vec4 m_maxEndCol{0.0F};
};

inline auto BasicColorGen::SetMinMaxStartColors(const glm::vec4& minColor,
                                                const glm::vec4& maxColor) noexcept -> void
{
  m_minStartCol = minColor;
  m_maxStartCol = maxColor;
}

inline auto BasicColorGen::SetMinMaxEndColors(const glm::vec4& minColor,
                                              const glm::vec4& maxColor) noexcept -> void
{
  m_minEndCol = minColor;
  m_maxEndCol = maxColor;
}

class BasicVelGen : public ParticleGenerator
{
public:
  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;

  auto SetMinMaxVelocity(const glm::vec4& minVelocity, const glm::vec4& maxVelocity) noexcept
      -> void;

private:
  glm::vec4 m_minStartVel{0.0F};
  glm::vec4 m_maxStartVel{0.0F};
};

inline auto BasicVelGen::SetMinMaxVelocity(const glm::vec4& minVelocity,
                                           const glm::vec4& maxVelocity) noexcept -> void
{
  m_minStartVel = minVelocity;
  m_maxStartVel = maxVelocity;
}

class SphereVelGen : public ParticleGenerator
{
public:
  float m_minVel = 0.0F;
  float m_maxVel = 0.0F;

public:
  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;
};

class VelFromPosGen : public ParticleGenerator
{
public:
  glm::vec4 m_offset{0.0F};
  float m_minScale = 0.0F;
  float m_maxScale = 0.0F;

public:
  VelFromPosGen(const glm::vec4& off, const double minS, const double maxS)
    : m_offset(off), m_minScale(static_cast<float>(minS)), m_maxScale(static_cast<float>(maxS))
  {
  }

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;
};

class BasicTimeGen : public ParticleGenerator
{
public:
  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void override;

  auto SetMinMaxTime(float minTime, float maxTime) noexcept -> void;

private:
  float m_minTime = 0.0F;
  float m_maxTime = 0.0F;
};

inline auto BasicTimeGen::SetMinMaxTime(const float minTime, const float maxTime) noexcept -> void
{
  m_minTime = minTime;
  m_maxTime = maxTime;
}

} // namespace particles::generators
