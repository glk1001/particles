#include "attractorEffect.h"

#include <cmath>

bool AttractorEffect::initialize(size_t numParticles)
{
	//
	// particles
	//
	const size_t NUM_PARTICLES = numParticles == 0 ? 250000 : numParticles;
	m_system = std::make_shared<particles::ParticleSystem>(NUM_PARTICLES);

	//
	// common
	//
	m_colGenerator = std::make_shared<particles::generators::BasicColorGen>();
	m_colGenerator->m_minStartCol = glm::vec4{ 0.99, 0.99, 0.99, 1.0 };
	m_colGenerator->m_maxStartCol = glm::vec4{ 0.99, 0.99, 1.0, 1.0 };
	m_colGenerator->m_minEndCol = glm::vec4{ 0.99, 0.99, 0.99, 0.0 };
	m_colGenerator->m_maxEndCol = glm::vec4{ 0.99, 0.99, 1.0, 0.25 };

	auto velGenerator = std::make_shared<particles::generators::SphereVelGen>();
	velGenerator->m_minVel = 0.1f;
	velGenerator->m_maxVel = 0.1f;

	auto timeGenerator = std::make_shared<particles::generators::BasicTimeGen>();
	timeGenerator->m_minTime = 1.6f;
	timeGenerator->m_maxTime = 4.0f;

	//
	// emitter 1:
	//
	auto particleEmitter = std::make_shared<particles::ParticleEmitter>();
	{
		particleEmitter->m_emitRate = (float)NUM_PARTICLES*0.1f;

		// pos:
		m_posGenerators[0] = std::make_shared<particles::generators::BoxPosGen>();
		m_posGenerators[0]->m_pos = glm::vec4{ 0.0, 0.0, -0.25, 0.0 };
		m_posGenerators[0]->m_maxStartPosOffset = glm::vec4{ 0.0, 0.0, 0.0, 0.0 };
		particleEmitter->addGenerator(m_posGenerators[0]);

		particleEmitter->addGenerator(m_colGenerator);
		particleEmitter->addGenerator(velGenerator);
		particleEmitter->addGenerator(timeGenerator);
	}
	m_system->addEmitter(particleEmitter);

	//
	// emitter 2:
	//
	auto particleEmitter2 = std::make_shared<particles::ParticleEmitter>();
	{
		particleEmitter2->m_emitRate = (float)NUM_PARTICLES*0.1f;

		m_posGenerators[1] = std::make_shared<particles::generators::BoxPosGen>();
		m_posGenerators[1]->m_pos = glm::vec4{ 0.0, 0.0, 0.25, 0.0 };
		m_posGenerators[1]->m_maxStartPosOffset = glm::vec4{ 0.0, 0.0, 0.0, 0.0 };
		particleEmitter2->addGenerator(m_posGenerators[1]);

		particleEmitter2->addGenerator(m_colGenerator);
		particleEmitter2->addGenerator(velGenerator);
		particleEmitter2->addGenerator(timeGenerator);
	}
	m_system->addEmitter(particleEmitter2);

	//
	// emitter 3:
	//
	auto particleEmitter3 = std::make_shared<particles::ParticleEmitter>();
	{
		particleEmitter3->m_emitRate = (float)NUM_PARTICLES*0.1f;

		m_posGenerators[2] = std::make_shared<particles::generators::BoxPosGen>();
		m_posGenerators[2]->m_pos = glm::vec4{ 0.0, 0.0, 0.25, 0.0 };
		m_posGenerators[2]->m_maxStartPosOffset = glm::vec4{ 0.0, 0.0, 0.0, 0.0 };
		particleEmitter3->addGenerator(m_posGenerators[2]);

		particleEmitter3->addGenerator(m_colGenerator);
		particleEmitter3->addGenerator(velGenerator);
		particleEmitter3->addGenerator(timeGenerator);
	}
	m_system->addEmitter(particleEmitter3);

	//
	// updaters:
	//
	auto timeUpdater = std::make_shared<particles::updaters::BasicTimeUpdater>();
	m_system->addUpdater(timeUpdater);

	auto colorUpdater = std::make_shared<particles::updaters::VelColorUpdater>();
	colorUpdater->m_minVel = glm::vec4{ -0.5f, -0.5f, -0.5f, 0.0f };
	colorUpdater->m_maxVel = glm::vec4{ 2.0f, 2.0f, 2.0f, 2.0f };
	m_system->addUpdater(colorUpdater);

	m_attractors = std::make_shared<particles::updaters::AttractorUpdater>();
	m_attractors->add(glm::vec4{ 0.0, 0.0, 0.75, 1.0 });
	m_attractors->add(glm::vec4{ 0.0, 0.0, -0.75, 1.0 });
	m_attractors->add(glm::vec4{ 0.0, 0.75, 0.0, 1.0 });
	m_attractors->add(glm::vec4{ 0.0, -0.75, 0.0, 1.0 });
	m_system->addUpdater(m_attractors);

	auto eulerUpdater = std::make_shared<particles::updaters::EulerUpdater>();
	eulerUpdater->m_globalAcceleration = glm::vec4{ 0.0, 0.0, 0.0, 0.0 };
	m_system->addUpdater(eulerUpdater);

	m_zScale = 1.0f;

	return true;
}

bool AttractorEffect::initializeRenderer()
{
	m_renderer = particles::RendererFactory::create("gl");
	m_renderer->generate(m_system.get(), false);

	return true;
}

void AttractorEffect::clean()
{
	if (m_renderer) m_renderer->destroy();
}

void AttractorEffect::update(double dt)
{
	static double time = 0.0;
	time += dt;

	m_posGenerators[0]->m_pos.x = 0.15f*sinf((float)time*2.5f);
	m_posGenerators[0]->m_pos.y = 0.15f*cosf((float)time*2.5f);
	m_posGenerators[0]->m_pos.z = m_zScale*0.25f*cosf((float)time*2.5f);

	m_posGenerators[1]->m_pos.x = -0.15f*sinf((float)time*2.f);
	m_posGenerators[1]->m_pos.y = 0.15f*cosf((float)time*2.f);
	m_posGenerators[1]->m_pos.z = m_zScale*0.25f*cosf((float)time*1.5f);

	m_posGenerators[2]->m_pos.x = -0.15f*sinf((float)time*1.5f);
	m_posGenerators[2]->m_pos.y = 0.15f*cosf((float)time*2.5f);
	m_posGenerators[2]->m_pos.z = m_zScale*0.25f*cosf((float)time*1.75f);
}

void AttractorEffect::cpuUpdate(double dt)
{
	m_system->update(dt);
}

void AttractorEffect::gpuUpdate(double dt)
{
	m_renderer->update();
}

void AttractorEffect::render()
{
	m_renderer->render();
}
