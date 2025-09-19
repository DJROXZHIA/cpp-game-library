#ifndef DJROXZHIA_ECS
#define DJROXZHIA_ECS

#include <memory>

#include <entt/entt.hpp>

#include "core/events/EventSystem.h"

namespace DJROXZHIA {

	struct System;

	class ECSManager
	{
	public:
		ECSManager();
		~ECSManager();

		entt::entity CreateEntity();
		void DestroyEntity(entt::entity e);

		void Update(const double& delta);

		void Restart();

		template<typename T>
		T& AddComponent(const T& component, entt::entity e)
		{
			assert(!HasComponent<T>(e));
			T& rcomponent = m_registry.emplace<T>(e, component);
			return rcomponent;
		}

		template<typename T>
		T& GetComponent(entt::entity e)
		{
			assert(HasComponent<T>(e));
			return m_registry.get<T>(e);
		}

		template<typename T>
		bool HasComponent(entt::entity e)
		{
			return m_registry.all_of<T>(e);
		}

		template<typename T>
		void RemoveComponent(entt::entity e)
		{
			if (HasComponent<T>(e))
			{
				m_registry.remove<T>(e);
			}
		}

		template<typename T>
		void RegisterSystem()
		{
			m_systems.emplace_back(std::make_unique<T>());
		}

		inline void AddEventRecipient(const char* event_name, EventCallback callback) { m_EventSystem.AddRecipient(event_name, callback); }
		inline void RemoveEventRecipient(const char* event_name) { m_EventSystem.RemoveRecipient(event_name); }
		inline void PublishEvent(const char* event_name, void* event_data) { m_EventSystem.Publish(event_name, event_data); }

		template <typename ...T>
		auto GetView()
		{
			return m_registry.view<T...>();
		}

	private:
		entt::registry m_registry;
		std::vector<std::unique_ptr<System>> m_systems;
		EventSystem m_EventSystem;
	};

}

#endif // !DJROXZHIA_ECS
