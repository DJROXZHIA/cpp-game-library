#ifndef DJROXZHIA_SCENE
#define DJROXZHIA_SCENE

#include <entt/entt.hpp>
#include "physics/Physics.h"

namespace DJROXZHIA {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();
		void DestroyEntity(const Entity& entity);

		void AddEntityToPhysicsWorld(const Entity& entity);

		void UpdatePhysics();

		virtual void Update() {};
		virtual void Render() {};

		template <typename ...T>
		auto GetViewEntities()
		{
			return m_registry.view<T...>();
		}

	protected:
		entt::registry m_registry;  //TODO:- CHANGE TO PRIVATE
		Physics m_physics;

		friend class Entity;
	};

}

#endif // !DJROXZHIA_SCENE

