#ifndef DJROXZHIA_SYSTEMS
#define DJROXZHIA_SYSTEMS

#include "ECSManager.h"
#include "Components.h"

#include "graphics/renderers/BatchRenderer2D.h"


namespace DJROXZHIA {

	struct System
	{
		virtual void Update(const double& deltatime, ECSManager* ecs) = 0;
	};

	struct RenderSystem : System
	{
		void Update(const double& deltatime, ECSManager* ecs) override
		{
			auto view = ecs->GetView<TransformComponent, SpriteComponent>();

			for (auto entity : view)
			{
				TransformComponent& transform_c = view.get<TransformComponent>(entity);
				SpriteComponent& sprite = view.get<SpriteComponent>(entity);

				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, transform_c.translation)
					* glm::rotate(transform, transform_c.rotationAngle, transform_c.rotation)
					* glm::scale(transform, transform_c.scale);

				BatchRenderer2D::Submit(transform, sprite.color, sprite.texture->GetTextureID());
			}

			BatchRenderer2D::EndSession();
			BatchRenderer2D::Flush();
			BatchRenderer2D::BeginSession();
		}
	};

	
	struct PhysicsSystem : System
	{
		void Update(const double& deltatime, ECSManager* ecs) override
		{
			auto view = ecs->GetView<TransformComponent, RigidBodyComponent>();

			for (auto entity : view)
			{
				TransformComponent& transform_c = view.get<TransformComponent>(entity);
				RigidBodyComponent& rigidbody = view.get<RigidBodyComponent>(entity);

				b2Vec2 position = rigidbody.body->GetPosition();
				transform_c.translation.x = position.x;
				transform_c.translation.y = position.y;

				transform_c.rotationAngle = rigidbody.body->GetAngle();
			}
		}
	};



	struct LightSystem : System
	{
		void Update(const double& deltatime, ECSManager* ecs) override
		{
			auto view = ecs->GetView<LightComponent>();

			Shader* shader = nullptr;
			if (view.get<LightComponent>(view.front()).shader != nullptr)
				shader = view.get<LightComponent>(view.front()).shader;
			else
				return;
			shader->Enable();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

			for (auto entity : view)
			{
				glm::vec3 pos = view.get<LightComponent>(entity).position;
				glm::vec3 size = view.get<LightComponent>(entity).size;
				glm::vec4 color = view.get<LightComponent>(entity).color;

				BatchRenderer2D::Submit(pos, size, color, 6);
			}
		}
	};

}

#endif // !DJROXZHIA_SYSTEMS

