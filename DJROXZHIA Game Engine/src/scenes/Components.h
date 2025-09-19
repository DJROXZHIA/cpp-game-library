#ifndef DJROXZHIA_COMPONENTS
#define DJROXZHIA_COMPONENTS

#include "glm/glm/glm.hpp"

#include <glm/glm/gtc/matrix_transform.hpp>

#include "graphics/Texture.h"
#include "graphics/renderers/BatchRenderer2D.h"

#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/gtx/quaternion.hpp>

namespace DJROXZHIA {

	struct TransformComponent
	{
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 1.0f);
		float rotationAngle = 0.0f;
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	};



	struct SpriteComponent
	{
		glm::vec4 color = glm::vec4(1.0f);
		Texture* texture;
	};

	

	struct RigidBodyComponent
	{
		enum class BodyType { Static = 0, Dynamic, Kinematic};

		BodyType type = BodyType::Static;

		b2Body* body = nullptr;
		b2FixtureDef fixture;
	};



	struct LightComponent
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 size = glm::vec3(1.0f);
		glm::vec4 color = glm::vec4(1.0f);
		Shader* shader = nullptr;
	};
}

#endif // !DJROXZHIA_COMPONENTS
