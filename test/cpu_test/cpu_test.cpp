#include <chrono>
#include <iostream>
#include <stdexcept>

import Particles.Effects.Effect;
import Particles.Effects.Attractor;
import Particles.Effects.Fountain;
import Particles.Effects.Tunnel;
import Particles.Particles;

using PARTICLES::EFFECTS::AttractorEffect;
using PARTICLES::EFFECTS::FountainEffect;
using PARTICLES::EFFECTS::IEffect;
using PARTICLES::EFFECTS::TunnelEffect;

namespace
{

class EffectFactory
{
public:
  [[nodiscard]] static auto create(const char* name,
                                   size_t numParticles) -> std::shared_ptr<IEffect>;
};

auto EffectFactory::create(const char* const name,
                           const size_t numParticles) -> std::shared_ptr<IEffect>
{
  const auto effect = std::string{name};

  if ("tunnel" == effect)
  {
    return std::make_shared<TunnelEffect>(numParticles);
  }
  if ("attractors" == effect)
  {
    return std::make_shared<AttractorEffect>(numParticles);
  }
  if ("fountain" == effect)
  {
    return std::make_shared<FountainEffect>(numParticles);
  }

  throw std::runtime_error("Effect not found.");
}

class CpuTimeQuery
{
public:
  auto begin() -> void { m_cpuTimePointStart = std::chrono::high_resolution_clock::now(); }

  auto end() -> void
  {
    const auto diff  = std::chrono::high_resolution_clock::now() - m_cpuTimePointStart;
    const auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    m_time           = 0.5 * (m_time + static_cast<double>(milli));
  }

  [[nodiscard]] auto GetTimeInMilliseconds() const -> double { return m_time; }

private:
  double m_time{};
  std::chrono::time_point<std::chrono::high_resolution_clock> m_cpuTimePointStart;
};

} // namespace

int main()
{
  static const std::vector<std::string> s_EFFECTS_NAME{"tunnel", "attractors", "fountain"};

  static constexpr auto START_NUM_PARTICLES = 1000U;
  static constexpr auto END_NUM_PARTICLES   = 301000U;
  static constexpr auto PARTICLES_NUM_STEPS = 30U;
  static constexpr auto NUM_PARTICLES_STEP =
      (END_NUM_PARTICLES - START_NUM_PARTICLES) / PARTICLES_NUM_STEPS;

  static constexpr auto DELTA_TIME  = 1.0 / 60.0; // 60 fps
  static constexpr auto FRAME_COUNT = 200U;

  CpuTimeQuery timer;

  std::cout << "count | ";
  for (const auto& n : s_EFFECTS_NAME)
  {
    std::cout << n.c_str() << " | ";
  }
  std::cout << "\n";
  std::cout << "-------|----------\n";

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(3);
  std::wcout << std::fixed;

  for (auto step = 0U; step < PARTICLES_NUM_STEPS; ++step)
  {
    const auto numParticles = START_NUM_PARTICLES + (step * NUM_PARTICLES_STEP);

    if ((numParticles < 150000) or (numParticles > 200000))
    {
      continue;
    }

    std::cout << numParticles << " | ";

    for (const auto& n : s_EFFECTS_NAME)
    {
      const auto effect = EffectFactory::create(n.c_str(), numParticles);

      timer.begin();
      for (auto frame = 0U; frame < FRAME_COUNT; ++frame)
      {
        effect->Update(DELTA_TIME);
      }
      timer.end();

      std::cout << timer.GetTimeInMilliseconds() << " | ";
    }
    std::cout << "\n";
  }

  std::cout << "time in milliseconds\n";

  return 0;
}
