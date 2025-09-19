#include "LightingSystem.h"

namespace DJROXZHIA {

	Shader* LightingSystem::m_shader = nullptr;
	float LightingSystem::m_ambient = 0.15f;
	int LightingSystem::m_lightsCount = 0;


	void LightingSystem::Init(Shader* shader, float ambient)
	{
		m_shader = shader;
		m_ambient = ambient;
	}

	void LightingSystem::Shutdown(){}

	void LightingSystem::SetLights(glm::vec2* position, glm::vec4* color, float* radius, int lightsCount)
	{
		m_shader->SetUniformVec2Pointer("u_lightPos", position, lightsCount);
		m_shader->SetUniformFloatPointer("u_lightRadius", radius, lightsCount);
		m_shader->SetUniformVec4Pointer("u_lightColor", color, lightsCount);
		m_shader->SetUniformInt("u_numLights", lightsCount);
		m_shader->SetUniformFloat("u_ambient", m_ambient);
	}

}