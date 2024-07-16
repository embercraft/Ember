#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Timestep.h"
#include "Ember/Scene/Entity.h"

namespace Ember
{

	class ScriptableEntity //: public Entity
	{
	public:
		ScriptableEntity() = default;
		virtual ~ScriptableEntity() = default;
		
		ScriptableEntity(const Entity& entity)
			: m_Entity(entity) {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}

	private:
		Entity m_Entity;
		friend class Scene;

	};

}