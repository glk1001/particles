#pragma once

#include "effect.h"
#include <memory>
#include "particles.h"
#include "particleGenerators.h"
#include "particleRenderer.h"
#include "particleUpdaters.h"


class TunnelEffect : public IEffect
{
private:
	std::shared_ptr<particles::ParticleSystem> m_system;
	std::shared_ptr<particles::IParticleRenderer> m_renderer;
	std::shared_ptr<particles::generators::RoundPosGen> m_posGenerator;
	std::shared_ptr<particles::generators::BasicColorGen> m_colGenerator;
public:
	bool initialize(size_t numParticles) override;
	bool initializeRenderer() override;
	void reset() override { m_system->reset(); }
	void clean() override;

        void update(double dt) override;
	void cpuUpdate(double dt) override;
	void gpuUpdate(double dt) override;
	void render() override;

	int numAllParticles() override { return m_system->numAllParticles(); }
	int numAliveParticles() override { return m_system->numAliveParticles(); }
};
