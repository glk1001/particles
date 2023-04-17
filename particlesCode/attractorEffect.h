#pragma once

#include "effect.h"

#include "particles.h"
#include "particleGenerators.h"
#include "particleRenderer.h"
#include "particleUpdaters.h"

#include <memory>

class AttractorEffect : public IEffect
{
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

      private:
        std::shared_ptr<particles::ParticleSystem> m_system;
        std::shared_ptr<particles::IParticleRenderer> m_renderer;
        std::shared_ptr<particles::generators::BoxPosGen> m_posGenerators[3];
        std::shared_ptr<particles::generators::BasicColorGen> m_colGenerator;
        std::shared_ptr<particles::updaters::AttractorUpdater> m_attractors;
        float m_zScale;
};
