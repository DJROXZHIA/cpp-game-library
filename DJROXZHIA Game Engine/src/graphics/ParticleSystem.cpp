#include "ParticleSystem.h"

#include "renderers/BatchRenderer2D.h"

#include <glm/glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/gtx/compatibility.hpp>

namespace DJROXZHIA {

	std::vector<ParticleSystem::Particle> ParticleSystem::m_particles = {};
	uint32_t ParticleSystem::m_nextParticlesIndex = 999;

	void ParticleSystem::Init()
	{
	}

	void ParticleSystem::Shutdown()
	{
	}

	void ParticleSystem::Update(const double& delta)
	{
		for (auto particle = m_particles.begin(); particle != m_particles.end();)
		{
			if (particle->lifeRemaining <= 0.0f)
			{
				particle = m_particles.erase(particle);
			}
			else
			{
				particle->lifeRemaining -= (float)delta;
				particle->position += particle->velocity * (float)delta;
				particle->rotation += 0.01f * (float)delta;
				++particle;
			}
		}
	}

	void ParticleSystem::Render()
	{
		for (Particle& particle : m_particles)
		{
			if (!particle.active)
				continue;

			float life = particle.lifeRemaining / particle.lifeTime;
			glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);

			float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(particle.position.x, particle.position.y, 0.0f));
			transform = glm::scale(transform, glm::vec3(size));

			BatchRenderer2D::Submit(transform, color, BatchRenderer2D::GetDefaultTexture());
		}
	}

	void ParticleSystem::Emit(const ParticleData& particleComponent, const glm::vec2& position)
	{
		Particle particle;
		particle.active = true;
		particle.position = position;
		particle.rotation = ((float)(rand()) / (float)(RAND_MAX/3.0f)) * glm::pi<float>();

		particle.velocity = particleComponent.velocity;
		particle.velocity.x += rand() % (int)(particleComponent.velocityVariation.x);
		particle.velocity.y += rand() % (int)(particleComponent.velocityVariation.y);

		particle.colorBegin = particleComponent.colorBegin;
		particle.colorEnd = particleComponent.colorEnd;

		particle.lifeTime = particleComponent.lifeTime;
		particle.lifeRemaining = particleComponent.lifeTime;
		particle.sizeBegin = particleComponent.sizeBegin + (rand() % (int)(particleComponent.sizeVariation));
		particle.sizeEnd = particleComponent.sizeEnd;

		m_particles.push_back(particle);
	}

}