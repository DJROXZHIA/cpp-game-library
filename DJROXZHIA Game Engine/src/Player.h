#ifndef DJROXZHIA_PLAYER
#define DJROXZHIA_PLAYER

#include "scenes/Entity.h"
#include "scenes/Components.h"
#include "core/events/Event.h"

class Player : public DJROXZHIA::Entity
{
public:
	Player(DJROXZHIA::Scene* scene)
		: DJROXZHIA::Entity(scene)
	{
		AddComponent<DJROXZHIA::TransformComponent>(DJROXZHIA::TransformComponent(glm::vec3(0.0f), glm::vec3(250.0f)));
		AddComponent<DJROXZHIA::SpriteComponent>(DJROXZHIA::SpriteComponent(glm::vec4(0.2f, 0.6f, 0.4f, 1.0f), "res/textures/taran.jpg"));
	}

	void Update()
	{
		float x = GetComponent<DJROXZHIA::RigidBodyComponent>().body->GetLinearVelocity().x;
		float y = GetComponent<DJROXZHIA::RigidBodyComponent>().body->GetLinearVelocity().y;

		float rotation = GetComponent<DJROXZHIA::RigidBodyComponent>().body->GetAngularVelocity();

		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_UP))
			y -= 2.5;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_LEFT))
			x -= 2.5;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_DOWN))
			y += 2.5;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_RIGHT))
			x += 2.5;

		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_Z))
			rotation -= 0.005;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_C))
			rotation += 0.005;

		GetComponent<DJROXZHIA::RigidBodyComponent>().body->SetAngularVelocity(rotation);

		GetComponent<DJROXZHIA::RigidBodyComponent>().body->SetLinearVelocity({x, y});
	}

	void Render()
	{

	}

	DJROXZHIA::Texture* GetTexture()
	{
		return &GetComponent<DJROXZHIA::SpriteComponent>().texture;
	}
};


#endif // !DJROXZHIA_PLAYER

