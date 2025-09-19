#ifndef DJROXZHIA_LIGHTING_SYSTEM
#define DJROXZHIA_LIGHTING_SYSTEM

#include "graphics/Shader.h"

namespace DJROXZHIA {

	class LightingSystem
	{
	public:
		void Init(Shader* shader, float ambient);
		void Shutdown();

		static void SetLights(glm::vec2* position, glm::vec4* color, float* radius, int lightsCount);

	private:
		static Shader* m_shader;
		static float m_ambient;
		static int m_lightsCount;

	};

}

#endif // !DJROXZHIA_LIGHTING_SYSTEM
