#include "ECSManager.h"
#include "Systems.h"

namespace DJROXZHIA {

	ECSManager::ECSManager()
	{
	}

	ECSManager::~ECSManager()
	{

	}

	entt::entity ECSManager::CreateEntity()
	{
		return m_registry.create();
	}

	void ECSManager::DestroyEntity(entt::entity e)
	{
		m_registry.destroy(e);
	}

	void ECSManager::Update(const double& delta)
	{
		for (auto& system : m_systems)
			system->Update(delta, this);
	}

	void ECSManager::Restart()
	{
		m_registry.clear();
	}
}