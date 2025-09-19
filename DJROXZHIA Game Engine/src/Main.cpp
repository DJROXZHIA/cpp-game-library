#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/renderables/Renderable2D.h"
#include "graphics/renderers/BatchRenderer2D.h"
#include "graphics/Cameras.h"
#include "graphics/buffers/FrameBuffer.h"

#include "audio/AudioManager.h"

#include "GUI/GUI.h"

#include "core/events/Event.h"
#include "core/Application.h"
#include "core/AssetPool.h"

#include "physics/Physics.h"

#include "scenes/ECSManager.h"
#include "scenes/Entity.h"
#include "scenes/Components.h"
#include "scenes/Systems.h"

#include "tile/Tilemap.h"
#include "tile/Tile.h"

GLenum err()
{
	return glGetError();
}


int main()
{
	DJROXZHIA::Window myWindow("My Window", 800, 600, 16, 9, false, false);
	
	DJROXZHIA::Application app(&myWindow);

	DJROXZHIA::Shader textureShader("res/shaders/vertex.vert", "res/shaders/fragment.frag");
	DJROXZHIA::Shader lightingShader("res/shaders/vertex.vert", "res/shaders/lighting.frag");
	lightingShader.Enable();
	lightingShader.SetTextures("u_textures");
	textureShader.Enable();
	textureShader.SetTextures("u_textures");

	DJROXZHIA::BatchRenderer2D::Init();

	DJROXZHIA::OrthographicCamera camera(0, 1280, 720, 0, 0.0f, 100.0f);
	
	textureShader.SetUniformMat4("u_projection", camera.GetProjectionMatrix());
	textureShader.SetUniformMat4("u_view", camera.GetViewMatrix());

	DJROXZHIA::GUI::Init(&myWindow);

	DJROXZHIA::Physics* physics = new DJROXZHIA::Physics(9.8f);

	DJROXZHIA::FrameBuffer* textureFramebuffer = new DJROXZHIA::FrameBuffer(1280, 720);
	DJROXZHIA::FrameBuffer* lightFramebuffer = new DJROXZHIA::FrameBuffer(1280, 720);

	lightingShader.Enable();
	lightingShader.SetUniformMat4("u_projection", camera.GetProjectionMatrix());
	lightingShader.SetUniformMat4("u_view", camera.GetViewMatrix());

	//-------------

	DJROXZHIA::TileMap* map = new DJROXZHIA::TileMap("res/world/world.world");
	map->SetTile(0, DJROXZHIA::Tile(0, 64, 64, DJROXZHIA::Texture("res/textures/wall.png"), true));
	map->SetTile(1, DJROXZHIA::Tile(1, 64, 64, DJROXZHIA::Texture("res/textures/tile.png"), false));

	DJROXZHIA::Texture lightTexture("res/textures/light2.png");
	std::cout << lightTexture.GetTextureID() << "\n";

	DJROXZHIA::ECSManager* ecs = new DJROXZHIA::ECSManager();

	//DJROXZHIA::Entity box = ecs->CreateEntity();
	//DJROXZHIA::TransformComponent& transform1 = ecs->AddComponent(DJROXZHIA::TransformComponent(), box);
	//transform1.translation = glm::vec3(50.0f, 100.0f, 0.0f);
	//transform1.scale = glm::vec3(250.0f);
	//ecs->AddComponent(DJROXZHIA::SpriteComponent(glm::vec4(0.46f, 0.25f, 0.0f, 1.0f)), box);
	//ecs->AddComponent(DJROXZHIA::RigidBodyComponent(DJROXZHIA::RigidBodyComponent::BodyType::Dynamic), box);
	//
	//DJROXZHIA::Entity ground = ecs->CreateEntity();
	//DJROXZHIA::TransformComponent& transform2 = ecs->AddComponent(DJROXZHIA::TransformComponent(), ground);
	//transform2.translation = glm::vec3(0.0f, 500.0f, 0.0f);
	//transform2.scale = glm::vec3(800.0f, 75.0f, 0.0f);
	//ecs->AddComponent(DJROXZHIA::RigidBodyComponent(DJROXZHIA::RigidBodyComponent::BodyType::Static), ground);
	//ecs->AddComponent(DJROXZHIA::SpriteComponent(glm::vec4(0.45f, 0.45f, 0.45f, 1.0f)), ground);

	DJROXZHIA::Entity light = ecs->CreateEntity();
	DJROXZHIA::LightComponent& lightComponent = ecs->AddComponent(DJROXZHIA::LightComponent(), light);
	lightComponent.position = glm::vec3(300.0f, 150.0f, 1.0f);
	lightComponent.size = glm::vec3(400.0f, 400.0f, 0.0f);
	lightComponent.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	lightComponent.shader = &lightingShader;

	DJROXZHIA::Entity light2 = ecs->CreateEntity();
	DJROXZHIA::LightComponent& lightComponent2 = ecs->AddComponent(DJROXZHIA::LightComponent(), light2);
	lightComponent2.position = glm::vec3(750.0f, 50.0f, 1.0f);
	lightComponent2.size = glm::vec3(150.0f, 150.0f, 0.0f);
	lightComponent2.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	lightComponent2.shader = &lightingShader;

	
	//physics->CreateBody(ecs, box);
	//physics->CreateBody(ecs, ground);

	ecs->RegisterSystem<DJROXZHIA::PhysicsSystem>();
	ecs->RegisterSystem<DJROXZHIA::RenderSystem>();
	ecs->RegisterSystem<DJROXZHIA::LightSystem>();

	while (app.Run(glm::vec4(0.15f, 0.15f, 0.15f, 1.0f)))
	{
		glm::vec3 camPos = camera.GetPosition();
		camPos.z = 2;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_W))
			camPos.y -= 5;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_A))
			camPos.x -= 5;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_S))
			camPos.y += 5;
		if (DJROXZHIA::KeyEvent::IsKeyPressed(GLFW_KEY_D))
			camPos.x += 5;

		camera.SetPosition(camPos);
		camera.UpdateViewMatrix();
		lightingShader.Enable();
		lightingShader.SetUniformMat4("u_view", camera.GetViewMatrix());
		textureShader.Enable();
		textureShader.SetUniformMat4("u_view", camera.GetViewMatrix());

		physics->Update();

		DJROXZHIA::BatchRenderer2D::BeginSession();

		map->Render();
		ecs->Update();

		DJROXZHIA::BatchRenderer2D::EndSession();
		DJROXZHIA::BatchRenderer2D::Flush();

		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		myWindow.Update();
	}

	delete physics;
	delete ecs;
}