#pragma once

#include "particles.h"

#include <vector>

namespace particles::generators
{

class BoxPosGen : public ParticleGenerator
{
public:
  glm::vec4 m_pos{0.0F};
  glm::vec4 m_maxStartPosOffset{0.0F};

public:
  auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void override;
};

class RoundPosGen : public ParticleGenerator
{
public:
  glm::vec4 m_center{0.0F};
  float m_radX = 0.0F;
  float m_radY = 0.0F;

public:
  RoundPosGen() = default;
  RoundPosGen(const glm::vec4& center, const double radX, const double radY)
    : m_center{center}, m_radX{static_cast<float>(radX)}, m_radY{static_cast<float>(radY)}
  {
  }

  auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void override;
};

class BasicColorGen : public ParticleGenerator
{
public:
  glm::vec4 m_minStartCol{0.0F};
  glm::vec4 m_maxStartCol{0.0F};
  glm::vec4 m_minEndCol{0.0F};
  glm::vec4 m_maxEndCol{0.0F};

public:
  auto generate(double dt, ParticleData* p, size_t startId, size_t endId)  -> void override;
};

class BasicVelGen : public ParticleGenerator
{
public:
  glm::vec4 m_minStartVel{0.0F};
  glm::vec4 m_maxStartVel{0.0F};

public:
  auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void override;
};

class SphereVelGen : public ParticleGenerator
{
public:
  float m_minVel = 0.0F;
  float m_maxVel = 0.0F;

public:
  auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void override;
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

  auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void override;
};

class BasicTimeGen : public ParticleGenerator
{
public:
  float m_minTime = 0.0F;
  float m_maxTime = 0.0F;

public:
  auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void override;
};

} // namespace particles::generators
