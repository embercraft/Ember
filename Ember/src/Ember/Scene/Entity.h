#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Scene/Scene.h"

#include <entt/entt.hpp>

namespace Ember
{

	class EMBER_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity() = default;

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			EMBER_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			EMBER_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			EMBER_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& UpdateComponent(Args&&... args)
		{
			EMBER_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.replace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};

}