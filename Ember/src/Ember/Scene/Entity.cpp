#include "Emberpch.h"
#include "Ember/Scene/Entity.h"

namespace Ember{

	Entity::Entity(entt::entity handle, Scene *scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}