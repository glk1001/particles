// FROM: https://www.cppstories.com/2015/04/flexible-particle-system-summary/

module;

#include <glm/vec4.hpp>
#include <limits>
#include <memory>
#include <vector>

export module Particles.Particles;

export namespace PARTICLES
{

class ParticleData
{
public:
  explicit ParticleData(size_t count) noexcept;

  auto Reset() noexcept -> void;

  auto Kill(size_t id) noexcept -> void;
  auto Wake(size_t id) noexcept -> void;
  auto SwapData(size_t a, size_t b) noexcept -> void;

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

  [[nodiscard]] auto GetColor(size_t i) const noexcept -> const glm::vec4&;
  auto SetColor(size_t i, const glm::vec4& color) noexcept -> void;

  [[nodiscard]] auto GetStartColor(size_t i) const noexcept -> const glm::vec4&;
  auto SetStartColor(size_t i, const glm::vec4& startColor) noexcept -> void;

  [[nodiscard]] auto GetEndColor(size_t i) const noexcept -> const glm::vec4&;
  auto SetEndColor(size_t i, const glm::vec4& endColor) noexcept -> void;

  [[nodiscard]] auto GetTime(size_t i) const noexcept -> const glm::vec4&;
  auto SetTime(size_t i, const glm::vec4& time) noexcept -> void;

  [[nodiscard]] static auto ComputeMemoryUsage(const ParticleData& particleData) noexcept -> size_t;

private:
  size_t m_count;
  size_t m_countAlive = 0U;

  std::vector<glm::vec4> m_position;
  std::vector<glm::vec4> m_velocity;
  std::vector<glm::vec4> m_acceleration;
  std::vector<glm::vec4> m_color;
  std::vector<glm::vec4> m_startColor;
  std::vector<glm::vec4> m_endColor;
  std::vector<glm::vec4> m_time;
  std::vector<bool> m_alive;

  static constexpr auto MEM_BYTES = +(2 * sizeof(size_t)) + (7 * sizeof(glm::vec4)) + sizeof(bool);
};

class ParticleEmitter;
class IParticleUpdater;

class ParticleSystem
{
public:
  explicit ParticleSystem(size_t maxCount);

  auto AddEmitter(const std::shared_ptr<ParticleEmitter>& emitter) noexcept -> void;
  auto AddUpdater(const std::shared_ptr<IParticleUpdater>& updater) noexcept -> void;

  auto Reset() noexcept -> void;

  auto Update(double dt) noexcept -> void;

  [[nodiscard]] auto GetNumAllParticles() const noexcept -> size_t;
  [[nodiscard]] auto GetNumAliveParticles() const noexcept -> size_t;
  [[nodiscard]] auto GetFinalData() const noexcept -> const ParticleData&;

  [[nodiscard]] static auto ComputeMemoryUsage(const ParticleSystem& particleSystem) noexcept
      -> size_t;

private:
  size_t m_count;
  ParticleData m_particles;

  std::vector<std::shared_ptr<ParticleEmitter>> m_emitters;
  std::vector<std::shared_ptr<IParticleUpdater>> m_updaters;
};

class IParticleGenerator;

class ParticleEmitter
{
public:
  ParticleEmitter() = default;

  auto SetEmitRate(float emitRate) noexcept -> void;
  auto SetMaxNumAliveParticles(size_t maxNumAliveParticles) noexcept -> void;
  auto AddGenerator(const std::shared_ptr<IParticleGenerator>& gen) noexcept -> void;

  // Calls all the generators and at the end it activates (wakes) particle.
  auto Emit(double dt, ParticleData& particleData) noexcept -> void;

private:
  float m_emitRate              = 0.0F;
  size_t m_maxNumAliveParticles = std::numeric_limits<size_t>::max();
  std::vector<std::shared_ptr<IParticleGenerator>> m_generators;

  [[nodiscard]] auto GetMaxAllowedNewParticles(
      double dt, const ParticleData& particleData) const noexcept -> size_t;
};

class IParticleGenerator
{
public:
  IParticleGenerator()                                             = default;
  IParticleGenerator(const IParticleGenerator&)                    = delete;
  IParticleGenerator(IParticleGenerator&&)                         = delete;
  virtual ~IParticleGenerator()                                    = default;
  auto operator=(const IParticleGenerator&) -> IParticleGenerator& = delete;
  auto operator=(IParticleGenerator&&) -> IParticleGenerator&      = delete;

  struct IdRange
  {
    size_t start;
    size_t end;
  };
  virtual auto Generate(double dt,
                        ParticleData& particleData,
                        const IdRange& idRange) noexcept -> void = 0;
};

class IParticleUpdater
{
public:
  IParticleUpdater()                                           = default;
  IParticleUpdater(const IParticleUpdater&)                    = delete;
  IParticleUpdater(IParticleUpdater&&)                         = delete;
  virtual ~IParticleUpdater()                                  = default;
  auto operator=(const IParticleUpdater&) -> IParticleUpdater& = delete;
  auto operator=(IParticleUpdater&&) -> IParticleUpdater&      = delete;

  virtual auto Update(double dt, ParticleData& particleData) noexcept -> void = 0;
};

} // namespace PARTICLES

namespace PARTICLES
{

inline auto ParticleData::Reset() noexcept -> void
{
  m_countAlive = 0U;
}

inline auto ParticleData::GetCount() const noexcept -> size_t
{
  return m_count;
}

inline auto ParticleData::ComputeMemoryUsage(
    [[maybe_unused]] const ParticleData& particleData) noexcept -> size_t
{
  return MEM_BYTES;
}

inline auto ParticleData::GetAliveCount() const noexcept -> size_t
{
  return m_countAlive;
}

inline auto ParticleData::GetPosition(const size_t i) const noexcept -> const glm::vec4&
{
  return m_position[i];
}

inline auto ParticleData::SetPosition(const size_t i, const glm::vec4& position) noexcept -> void
{
  m_position[i] = position;
}

inline auto ParticleData::IncPosition(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_position[i] += amount;
}

inline auto ParticleData::GetVelocity(const size_t i) const noexcept -> const glm::vec4&
{
  return m_velocity[i];
}

inline auto ParticleData::SetVelocity(const size_t i, const glm::vec4& velocity) noexcept -> void
{
  m_velocity[i] = velocity;
}

inline auto ParticleData::IncVelocity(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_velocity[i] += amount;
}

inline auto ParticleData::DecVelocity(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_velocity[i] -= amount;
}

inline auto ParticleData::GetAcceleration(const size_t i) const noexcept -> const glm::vec4&
{
  return m_acceleration[i];
}

inline auto ParticleData::SetAcceleration(const size_t i,
                                          const glm::vec4& acceleration) noexcept -> void
{
  m_acceleration[i] = acceleration;
}

inline auto ParticleData::IncAcceleration(const size_t i, const glm::vec4& amount) noexcept -> void
{
  m_acceleration[i] += amount;
}

inline auto ParticleData::GetColor(const size_t i) const noexcept -> const glm::vec4&
{
  return m_color[i];
}

inline auto ParticleData::SetColor(const size_t i, const glm::vec4& color) noexcept -> void
{
  m_color[i] = color;
}

inline auto ParticleData::GetStartColor(const size_t i) const noexcept -> const glm::vec4&
{
  return m_startColor[i];
}

inline auto ParticleData::SetStartColor(const size_t i,
                                        const glm::vec4& startColor) noexcept -> void
{
  m_startColor[i] = startColor;
}

inline auto ParticleData::GetEndColor(const size_t i) const noexcept -> const glm::vec4&
{
  return m_endColor[i];
}

inline auto ParticleData::SetEndColor(const size_t i, const glm::vec4& endColor) noexcept -> void
{
  m_endColor[i] = endColor;
}

inline auto ParticleData::GetTime(const size_t i) const noexcept -> const glm::vec4&
{
  return m_time[i];
}

inline auto ParticleData::SetTime(const size_t i, const glm::vec4& time) noexcept -> void
{
  m_time[i] = time;
}

inline auto ParticleSystem::GetNumAllParticles() const noexcept -> size_t
{
  return m_particles.GetCount();
}

inline auto ParticleSystem::GetNumAliveParticles() const noexcept -> size_t
{
  return m_particles.GetAliveCount();
}

inline auto ParticleSystem::AddEmitter(const std::shared_ptr<ParticleEmitter>& emitter) noexcept
    -> void
{
  m_emitters.push_back(emitter);
}

inline auto ParticleSystem::AddUpdater(const std::shared_ptr<IParticleUpdater>& updater) noexcept
    -> void
{
  m_updaters.push_back(updater);
}

inline auto ParticleSystem::GetFinalData() const noexcept -> const ParticleData&
{
  return m_particles;
}

inline auto ParticleEmitter::SetEmitRate(const float emitRate) noexcept -> void
{
  m_emitRate = emitRate;
}

inline auto ParticleEmitter::SetMaxNumAliveParticles(const size_t maxNumAliveParticles) noexcept
    -> void
{
  m_maxNumAliveParticles = maxNumAliveParticles;
}

inline auto ParticleEmitter::AddGenerator(const std::shared_ptr<IParticleGenerator>& gen) noexcept
    -> void
{
  m_generators.push_back(gen);
}

} // namespace PARTICLES
