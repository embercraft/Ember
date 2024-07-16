#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Timestep.h"

#include <entt/entt.hpp>

namespace Ember
{
	class EMBER_API Entity; // Forward declaration

	class EMBER_API Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		
		entt::registry m_Registry{ };
		friend class Entity;
		friend class SceneHierarchyPanel;

	};
}