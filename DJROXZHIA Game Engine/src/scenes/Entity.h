#ifndef DJROXZHIA_ENTITY
#define DJROXZHIA_ENTITY

#include <entt/entt.hpp>

namespace DJROXZHIA {

	class Entity
	{
	public:
		Entity(entt::entity id);
		Entity(){}
		~Entity();

		operator entt::entity() const { return m_id; }
		inline entt::entity GetID() { return m_id; }

	private:
		entt::entity m_id = entt::null;
	};

}

#endif // !DJROXZHIA_ENTITY