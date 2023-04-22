#pragma once

#include "particles.h"

#include <vector>

namespace PARTICLES::GENERATORS
{

class BoxPosGen : public IParticleGenerator
{
public:
  BoxPosGen(const glm::vec4& position, const glm::vec4& maxStartPosOffset) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  glm::vec4 m_pos;
  glm::vec4 m_maxStartPosOffset;
};

class RoundPosGen : public IParticleGenerator
{
public:
  RoundPosGen(const glm::vec4& center, double radX, double radY) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  glm::vec4 m_center;
  float m_radX;
  float m_radY;
};

class BasicColorGen : public IParticleGenerator
{
public:
  BasicColorGen(const glm::vec4& minStartColor,
                const glm::vec4& maxStartColor,
                const glm::vec4& minEndColor,
                const glm::vec4& maxEndColor) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  glm::vec4 m_minStartCol;
  glm::vec4 m_maxStartCol;
  glm::vec4 m_minEndCol;
  glm::vec4 m_maxEndCol;
};

class BasicVelGen : public IParticleGenerator
{
public:
  BasicVelGen(const glm::vec4& minStartVelocity, const glm::vec4& maxStartVelocity) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  glm::vec4 m_minStartVel;
  glm::vec4 m_maxStartVel;
};

class SphereVelGen : public IParticleGenerator
{
public:
  SphereVelGen(float minVelocity, float maxVelocity) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  float m_minVel;
  float m_maxVel;
};

class VelFromPosGen : public IParticleGenerator
{
public:
  VelFromPosGen(const glm::vec4& offset, float minScale, float maxScale) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  glm::vec4 m_offset;
  float m_minScale;
  float m_maxScale;
};

class BasicTimeGen : public IParticleGenerator
{
public:
  BasicTimeGen(float minTime, float maxTime) noexcept;

  auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId) noexcept
      -> void override;

private:
  float m_minTime;
  float m_maxTime;
};

} // namespace PARTICLES::GENERATORS
