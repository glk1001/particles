#pragma once

#include <glm/vec4.hpp>
#include <memory>
#include <vector>

namespace PARTICLES
{

class ParticleData
{
public:
  explicit ParticleData(size_t count) noexcept;
  ParticleData(const ParticleData&)                    = delete;
  ParticleData(ParticleData&&)                         = delete;
  ~ParticleData()                                      = default;
  auto operator=(const ParticleData&) -> ParticleData& = delete;
  auto operator=(ParticleData&&) -> ParticleData&      = delete;

  auto reset() noexcept -> void;

  auto kill(size_t id) -> void;
  auto wake(size_t id) -> void;
  auto swapData(size_t a, size_t b) -> void;

  [[nodiscard]] auto GetCount() const noexcept -> size_t;
  [[nodiscard]] auto GetAliveCount() const noexcept -> size_t;

  [[nodiscard]] auto GetPosition(size_t i) const noexcept -> const glm::vec4&;
  auto SetPosition(size_t i, const glm::vec4& position) noexcept -> void;
  auto IncPosition(size_t i, const glm::vec4& amount) noexcept -> void;

  [[nodiscard]] auto GetVelocity(size_t i) const noexcept -> const glm::vec4&;
  auto SetVelocity(size_t i, const glm::vec4& velocity) noexcept -> void;
  auto IncVelocity(size_t i, const glm::vec4& amount) noexcept -> void;
  auto DecVelocity(size_t i, const glm::vec4& amount) noexcept -> void;

  [[nodiscard]] auto GetAcceleration(size_t i) const noexcept -> const glm::vec4&;
  auto SetAcceleration(size_t i, const glm::vec4& acceleration) noexcept -> void;
  auto IncAcceleration(size_t i, const glm::vec4& amount) noexcept -> void;
  auto DecAcceleration(size_t i, const glm::vec4& amount) noexcept -> void;

  [[nodiscard]] auto GetColor(size_t i) const noexcept -> const glm::vec4&;
  auto SetColor(size_t i, const glm::vec4& color) noexcept -> void;

  [[nodiscard]] auto GetStartColor(size_t i) const noexcept -> const glm::vec4&;
  auto SetStartColor(size_t i, const glm::vec4& startColor) noexcept -> void;

  [[nodiscard]] auto GetEndColor(size_t i) const noexcept -> const glm::vec4&;
  auto SetEndColor(size_t i, const glm::vec4& endColor) noexcept -> void;

  [[nodiscard]] auto GetTime(size_t i) const noexcept -> const glm::vec4&;
  auto SetTime(size_t i, const glm::vec4& time) noexcept -> void;
  auto DecTime(size_t i, const glm::vec4& amount) noexcept -> void;

  static auto copyOnlyAlive(const ParticleData* source, ParticleData* destination) -> void;
  [[nodiscard]] static auto computeMemoryUsage(const ParticleData& particleData) -> size_t;

private:
  size_t m_count;
  size_t m_countAlive = 0U;

  std::vector<glm::vec4> m_pos;
  std::vector<glm::vec4> m_vel;
  std::vector<glm::vec4> m_acc;
  std::vector<glm::vec4> m_col;
  std::vector<glm::vec4> m_startCol;
  std::vector<glm::vec4> m_endCol;
  std::vector<glm::vec4> m_time;
  std::vector<bool> m_alive;
};

inline auto ParticleData::reset() noexcept -> void
{
  m_countAlive = 0U;
}

inline auto ParticleData::GetCount() const noexcept -> size_t
{
  return m_count;
}

inline auto ParticleData::GetAliveCount() const noexcept -> size_t
{
  return m_countAlive;
}

inline auto ParticleData::GetPosition(const size_t i) const noexcept -> const glm::vec4&
{
  return m_pos[i];
}

inline auto ParticleData::SetPosition(const size_t i, const glm::vec4& position) noexcept -> void
{
  m_pos[i] = position;
}

inline auto ParticleData::IncPosition(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_pos[i] += amount;
}

inline auto ParticleData::GetVelocity(const size_t i) const noexcept -> const glm::vec4&
{
  return m_vel[i];
}

inline auto ParticleData::SetVelocity(const size_t i, const glm::vec4& velocity) noexcept -> void
{
  m_vel[i] = velocity;
}

inline auto ParticleData::IncVelocity(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_vel[i] += amount;
}

inline auto ParticleData::DecVelocity(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_vel[i] -= amount;
}

inline auto ParticleData::GetAcceleration(const size_t i) const noexcept -> const glm::vec4&
{
  return m_acc[i];
}

inline auto ParticleData::SetAcceleration(const size_t i, const glm::vec4& acceleration) noexcept
    -> void
{
  m_acc[i] = acceleration;
}

inline auto ParticleData::IncAcceleration(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_acc[i] += amount;
}

inline auto ParticleData::DecAcceleration(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_acc[i] -= amount;
}

inline auto ParticleData::GetColor(const size_t i) const noexcept -> const glm::vec4&
{
  return m_col[i];
}

inline auto ParticleData::SetColor(const size_t i, const glm::vec4& color) noexcept -> void
{
  m_col[i] = color;
}

inline auto ParticleData::GetStartColor(const size_t i) const noexcept -> const glm::vec4&
{
  return m_startCol[i];
}

inline auto ParticleData::SetStartColor(const size_t i, const glm::vec4& startColor) noexcept
    -> void
{
  m_startCol[i] = startColor;
}

inline auto ParticleData::GetEndColor(const size_t i) const noexcept -> const glm::vec4&
{
  return m_endCol[i];
}

inline auto ParticleData::SetEndColor(const size_t i, const glm::vec4& endColor) noexcept -> void
{
  m_endCol[i] = endColor;
}

inline auto ParticleData::GetTime(const size_t i) const noexcept -> const glm::vec4&
{
  return m_time[i];
}

inline auto ParticleData::SetTime(const size_t i, const glm::vec4& time) noexcept -> void
{
  m_time[i] = time;
}

inline auto ParticleData::DecTime(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_time[i] -= amount;
}

class ParticleGenerator
{
public:
  ParticleGenerator()                                            = default;
  ParticleGenerator(const ParticleGenerator&)                    = delete;
  ParticleGenerator(ParticleGenerator&&)                         = delete;
  virtual ~ParticleGenerator()                                   = default;
  auto operator=(const ParticleGenerator&) -> ParticleGenerator& = delete;
  auto operator=(ParticleGenerator&&) -> ParticleGenerator&      = delete;

  virtual auto generate(double dt, ParticleData* particleData, size_t startId, size_t endId)
      -> void = 0;
};

class ParticleEmitter
{
public:
  ParticleEmitter()                                          = default;
  ParticleEmitter(const ParticleEmitter&)                    = delete;
  ParticleEmitter(ParticleEmitter&&)                         = delete;
  virtual ~ParticleEmitter()                                 = default;
  auto operator=(const ParticleEmitter&) -> ParticleEmitter& = delete;
  auto operator=(ParticleEmitter&&) -> ParticleEmitter&      = delete;

  auto SetEmitRate(float emitRate) noexcept -> void;
  auto addGenerator(const std::shared_ptr<ParticleGenerator>& gen) noexcept -> void;

  // Calls all the generators and at the end it activates (wakes) particle.
  auto emit(double dt, ParticleData* particleData) -> void;

private:
  float m_emitRate = 0.0F;
  std::vector<std::shared_ptr<ParticleGenerator>> m_generators{};
};

inline auto ParticleEmitter::SetEmitRate(const float emitRate) noexcept -> void
{
  m_emitRate = emitRate;
}

inline auto ParticleEmitter::addGenerator(const std::shared_ptr<ParticleGenerator>& gen) noexcept
    -> void
{
  m_generators.push_back(gen);
}

class ParticleUpdater
{
public:
  ParticleUpdater()                                          = default;
  ParticleUpdater(const ParticleUpdater&)                    = delete;
  ParticleUpdater(ParticleUpdater&&)                         = delete;
  virtual ~ParticleUpdater()                                 = default;
  auto operator=(const ParticleUpdater&) -> ParticleUpdater& = delete;
  auto operator=(ParticleUpdater&&) -> ParticleUpdater&      = delete;

  virtual auto update(double dt, ParticleData* particleData) -> void = 0;
};

class ParticleSystem
{
public:
  explicit ParticleSystem(size_t maxCount);
  ParticleSystem(const ParticleSystem&)                    = delete;
  ParticleSystem(ParticleSystem&&)                         = delete;
  virtual ~ParticleSystem()                                = default;
  auto operator=(const ParticleSystem&) -> ParticleSystem& = delete;
  auto operator=(ParticleSystem&&) -> ParticleSystem&      = delete;

  auto update(double dt) -> void;
  auto reset() -> void;

  [[nodiscard]] auto numAllParticles() const -> size_t { return m_particles.GetCount(); }
  [[nodiscard]] auto numAliveParticles() const -> size_t { return m_particles.GetAliveCount(); }

  auto addEmitter(const std::shared_ptr<ParticleEmitter>& em) -> void { m_emitters.push_back(em); }
  auto addUpdater(const std::shared_ptr<ParticleUpdater>& up) -> void { m_updaters.push_back(up); }

  [[nodiscard]] auto finalData() const -> const ParticleData* { return &m_particles; }

  [[nodiscard]] static auto computeMemoryUsage(const ParticleSystem& particleSystem) -> size_t;

private:
  size_t m_count;
  ParticleData m_particles;
  ParticleData m_aliveParticles;

  std::vector<std::shared_ptr<ParticleEmitter>> m_emitters{};
  std::vector<std::shared_ptr<ParticleUpdater>> m_updaters{};
};

} // namespace PARTICLES
