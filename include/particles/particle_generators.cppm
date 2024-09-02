module;

#include <glm/vec4.hpp>

export module Particles.ParticleGenerators;

import Particles.Particles;

export namespace PARTICLES::GENERATORS
{

class BoxPositionGenerator : public IParticleGenerator
{
public:
  BoxPositionGenerator(const glm::vec4& position, const glm::vec4& maxStartPositionOffset) noexcept;

  auto SetPosition(const glm::vec4& position) noexcept -> void;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  glm::vec4 m_position;
  glm::vec4 m_maxStartPositionOffset;
};

class RoundPositionGenerator : public IParticleGenerator
{
public:
  RoundPositionGenerator(const glm::vec4& center, double xRadius, double yRadius) noexcept;

  auto SetCentreAndRadius(const glm::vec4& center, float xRadius, float yRadius) noexcept -> void;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  glm::vec4 m_center;
  float m_xRadius;
  float m_yRadius;
};

class BasicColorGenerator : public IParticleGenerator
{
public:
  BasicColorGenerator(const glm::vec4& minStartColor,
                      const glm::vec4& maxStartColor,
                      const glm::vec4& minEndColor,
                      const glm::vec4& maxEndColor) noexcept;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  glm::vec4 m_minStartColor;
  glm::vec4 m_maxStartColor;
  glm::vec4 m_minEndColor;
  glm::vec4 m_maxEndColor;
};

class BasicVelocityGenerator : public IParticleGenerator
{
public:
  BasicVelocityGenerator(const glm::vec4& minStartVelocity,
                         const glm::vec4& maxStartVelocity) noexcept;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  glm::vec4 m_minStartVelocity;
  glm::vec4 m_maxStartVelocity;
};

class SphereVelocityGenerator : public IParticleGenerator
{
public:
  SphereVelocityGenerator(float minVelocity, float maxVelocity) noexcept;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  float m_minVelocity;
  float m_maxVelocity;
};

class VelocityFromPositionGenerator : public IParticleGenerator
{
public:
  VelocityFromPositionGenerator(const glm::vec4& offset, float minScale, float maxScale) noexcept;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  glm::vec4 m_offset;
  float m_minScale;
  float m_maxScale;
};

class BasicTimeGenerator : public IParticleGenerator
{
public:
  BasicTimeGenerator(float minTime, float maxTime) noexcept;

  auto Generate(double dt, ParticleData& particleData, const IdRange& idRange) noexcept
      -> void override;

private:
  float m_minTime;
  float m_maxTime;
};

} // namespace PARTICLES::GENERATORS

namespace PARTICLES::GENERATORS
{

inline auto BoxPositionGenerator::SetPosition(const glm::vec4& position) noexcept -> void
{
  m_position = position;
}

inline auto RoundPositionGenerator::SetCentreAndRadius(const glm::vec4& center,
                                                       const float xRadius,
                                                       const float yRadius) noexcept -> void
{
  m_center  = center;
  m_xRadius = xRadius;
  m_yRadius = yRadius;
}

} // namespace PARTICLES::GENERATORS
