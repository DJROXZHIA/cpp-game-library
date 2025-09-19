#ifndef DJROXZHIA_PARTICLESYSTEM
#define DJROXZHIA_PARTICLESYSTEM

#include "glm/glm/glm.hpp"

#include <vector>

namespace DJROXZHIA {

	struct ParticleData
	{
		glm::vec2 velocity, velocityVariation;
		glm::vec4 colorBegin, colorEnd;
		float sizeBegin, sizeEnd, sizeVariation;
		float lifeTime = 1.0f;
	};

	class ParticleSystem
	{
	public:
		static void Init();
		static void Shutdown();

		static void Update(const double& delta);
		static void Render();

		static void Emit(const ParticleData& particle_data, const glm::vec2& position);

	private:
		struct Particle
		{
			glm::vec2 position, velocity;
			glm::vec4 colorBegin, colorEnd;
			float rotation = 0.0f;
			float sizeBegin, sizeEnd, lifeTime = 1.0f, lifeRemaining = 0.0f;
			bool active = false;
		};

		static std::vector<Particle> m_particles;
		static uint32_t m_nextParticlesIndex;


	};

}

#endif // !DJROXZHIA_PARTICLESYSTEM
