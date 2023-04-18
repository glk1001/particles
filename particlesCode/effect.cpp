#include "effect.h"

#include "attractorEffect.h"
#include "fountainEffect.h"
#include "tunnelEffect.h"

#include <string>

auto EffectFactory::create(const char* const name) -> std::shared_ptr<IEffect>
{
  const auto effect = std::string{name};

  if ("tunnel" == effect)
  {
    return std::make_shared<TunnelEffect>();
  }
  if ("attractors" == effect)
  {
    return std::make_shared<AttractorEffect>();
  }
  if ("fountain" == effect)
  {
    return std::make_shared<FountainEffect>();
  }

  return nullptr;
}
