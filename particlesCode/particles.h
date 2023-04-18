#pragma once

#include <glm/vec4.hpp>
#include <memory>
#include <vector>

namespace particles
{

class ParticleData
{
public:
  std::unique_ptr<glm::vec4[]> m_pos;
  std::unique_ptr<glm::vec4[]> m_col;
  std::unique_ptr<glm::vec4[]> m_startCol;
  std::unique_ptr<glm::vec4[]> m_endCol;
  std::unique_ptr<glm::vec4[]> m_vel;
  std::unique_ptr<glm::vec4[]> m_acc;
  std::unique_ptr<glm::vec4[]> m_time;
  std::unique_ptr<bool[]> m_alive;

  size_t m_count{0};
  size_t m_countAlive{0};

public:
  ParticleData()                                       = default;
  ParticleData(const ParticleData&)                    = delete;
  ParticleData(ParticleData&&)                         = delete;
  ~ParticleData()                                      = default;
  auto operator=(const ParticleData&) -> ParticleData& = delete;
  auto operator=(ParticleData&&) -> ParticleData&      = delete;

  auto generate(size_t maxSize) -> void;
  auto kill(size_t id) -> void;
  auto wake(size_t id) -> void;
  auto swapData(size_t a, size_t b) -> void;

  static auto copyOnlyAlive(const ParticleData* source, ParticleData* destination) -> void;
  [[nodiscard]] static auto computeMemoryUsage(const ParticleData& p) -> size_t;
};

class ParticleGenerator
{
public:
  ParticleGenerator()                                            = default;
  ParticleGenerator(const ParticleGenerator&)                    = delete;
  ParticleGenerator(ParticleGenerator&&)                         = delete;
  virtual ~ParticleGenerator()                                   = default;
  auto operator=(const ParticleGenerator&) -> ParticleGenerator& = delete;
  auto operator=(ParticleGenerator&&) -> ParticleGenerator&      = delete;

  virtual auto generate(double dt, ParticleData* p, size_t startId, size_t endId) -> void = 0;
};

class ParticleEmitter
{
public:
  float m_emitRate{0.0};

public:
  ParticleEmitter()                                          = default;
  ParticleEmitter(const ParticleEmitter&)                    = delete;
  ParticleEmitter(ParticleEmitter&&)                         = delete;
  virtual ~ParticleEmitter()                                 = default;
  auto operator=(const ParticleEmitter&) -> ParticleEmitter& = delete;
  auto operator=(ParticleEmitter&&) -> ParticleEmitter&      = delete;

  // calls all the generators and at the end it activates (wakes) particle
  virtual auto emit(double dt, ParticleData* p) -> void;

  auto addGenerator(const std::shared_ptr<ParticleGenerator> gen) -> void
  {
    m_generators.push_back(gen);
  }

protected:
  std::vector<std::shared_ptr<ParticleGenerator>> m_generators;
};

class ParticleUpdater
{
public:
  ParticleUpdater()                                          = default;
  ParticleUpdater(const ParticleUpdater&)                    = delete;
  ParticleUpdater(ParticleUpdater&&)                         = delete;
  virtual ~ParticleUpdater()                                 = default;
  auto operator=(const ParticleUpdater&) -> ParticleUpdater& = delete;
  auto operator=(ParticleUpdater&&) -> ParticleUpdater&      = delete;

  virtual auto update(double dt, ParticleData* p) -> void = 0;
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

  virtual auto update(double dt) -> void;
  virtual auto reset() -> void;

  [[nodiscard]] virtual auto numAllParticles() const -> size_t { return m_particles.m_count; }
  [[nodiscard]] virtual auto numAliveParticles() const -> size_t
  {
    return m_particles.m_countAlive;
  }

  auto addEmitter(const std::shared_ptr<ParticleEmitter> em) -> void { m_emitters.push_back(em); }
  auto addUpdater(const std::shared_ptr<ParticleUpdater> up) -> void { m_updaters.push_back(up); }

  [[nodiscard]] auto finalData() const -> const ParticleData* { return &m_particles; }
  [[nodiscard]] auto finalData() -> ParticleData* { return &m_particles; }

  [[nodiscard]] static auto computeMemoryUsage(const ParticleSystem& p) -> size_t;

protected:
  ParticleData m_particles;
  ParticleData m_aliveParticles;

  size_t m_count;

  std::vector<std::shared_ptr<ParticleEmitter>> m_emitters;
  std::vector<std::shared_ptr<ParticleUpdater>> m_updaters;
};

} // namespace particles
