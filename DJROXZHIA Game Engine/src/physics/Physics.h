#ifndef DJROXZHIA_PHYSICS
#define DJROXZHIA_PHYSICS

#include "glm/glm/glm.hpp"

#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

#include "scenes/ECSManager.h"
#include "scenes/Entity.h"

namespace DJROXZHIA {

	class Physics
	{
	public:
		Physics(const float& gravity);
		~Physics();

		void CreateBody(ECSManager* ecs, Entity entity);

		inline void SetGravity(const b2Vec2& gravity) { m_world.SetGravity(gravity); }
		inline b2Vec2 GetGravity() { return m_world.GetGravity(); }

		void Update();

	private:
		b2World m_world;
		b2Vec2 m_gravity;

		float m_timestep = 1.0f / 60.0f;
		int32 m_velocityIterations = 6;
		int32 m_positionIterations = 2;
	};

}

#endif // !DJROXZHIA_PHYSICS

