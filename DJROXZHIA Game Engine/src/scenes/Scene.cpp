#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace DJROXZHIA {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		entt::entity e = m_registry.create();
		return e;
	}

	void Scene::DestroyEntity(const Entity& entity)
	{
		m_registry.destroy(entity);
	}

	void Scene::AddEntityToPhysicsWorld(const Entity& entity)
	{
		m_physics.CreateBody(entity);
	}

	void Scene::UpdatePhysics()
	{
		m_physics.Update();
		auto view = GetViewEntities<RigidBodyComponent, TransformComponent>();

		for (auto entity : view)
		{
			auto [rigidbody, transform] = view.get<RigidBodyComponent, TransformComponent>(entity);
			
			b2Body* body = rigidbody.body;
			transform.translation = glm::vec3(body->GetPosition().x, body->GetPosition().y, 0.1f);
			transform.rotationAngle = body->GetAngle();
		}
	}
}