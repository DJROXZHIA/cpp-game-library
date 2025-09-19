#ifndef DJROXZHIA_GAMESCENE
#define DJROXZHIA_GAMESCENE

#include <vector>

#include "scenes/Scene.h"
#include "Player.h"
#include "graphics/renderers/BatchRenderer2D.h"

class GameScene : public DJROXZHIA::Scene
{
public:

	GameScene()
	{
	}

	void Update()
	{
		for (DJROXZHIA::Entity* e : m_entities)
		{
			e->Update();
		}
		UpdatePhysics();
	}

	void Render() override
	{
		auto a = GetViewEntities<DJROXZHIA::SpriteComponent, DJROXZHIA::TransformComponent>();

		for (auto entity : a)
		{
			auto [sprite, transform] = a.get<DJROXZHIA::SpriteComponent, DJROXZHIA::TransformComponent>(entity);
			//glm::mat4 model = glm::mat4(1.0f);
			//model = glm::translate(glm::mat4(1.0f), transform.position) * glm::scale(glm::mat4(1.0f), glm::vec3(transform.size, 0.0f));
			DJROXZHIA::BatchRenderer2D::Submit(transform.GetTransform(), sprite.color, sprite.texture.GetTextureID());
		}
	}

	void AddEntity(DJROXZHIA::Entity* e)
	{
		m_entities.push_back(e);
	}

private:
	std::vector<DJROXZHIA::Entity*>	m_entities;

};

#endif // !1
