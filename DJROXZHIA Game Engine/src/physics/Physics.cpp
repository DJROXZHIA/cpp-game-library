#include "Physics.h"
#include "scenes/Entity.h"
#include "scenes/Components.h"

namespace DJROXZHIA {

	Physics::Physics(const float& gravity)
		: m_gravity({0.0f, gravity }), m_world({ 0.0f, gravity }) {}

	Physics::~Physics(){} 

	void Physics::CreateBody(ECSManager* ecs, Entity entity)
	{
		TransformComponent& transform_c = ecs->GetComponent<TransformComponent>(entity);
		RigidBodyComponent& rigidbody = ecs->GetComponent<RigidBodyComponent>(entity);
		
		b2BodyDef def;
		
		switch (rigidbody.type)
		{
		case RigidBodyComponent::BodyType::Static: def.type = b2_staticBody; break;
		case RigidBodyComponent::BodyType::Dynamic: def.type = b2_dynamicBody; break;
		case RigidBodyComponent::BodyType::Kinematic: def.type = b2_kinematicBody; break;
		}

		def.position.Set(transform_c.translation.x, transform_c.translation.y);
		b2Body* body = m_world.CreateBody(&def);

		b2PolygonShape shape;
		shape.SetAsBox(transform_c.scale.x / 2, transform_c.scale.y / 2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		rigidbody.body = body;
		rigidbody.fixture = fixtureDef;
	}

	void Physics::Update()
	{
		m_world.Step(m_timestep, m_velocityIterations, m_positionIterations);
	}

}