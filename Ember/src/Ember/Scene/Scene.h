#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Timestep.h"
#include "Ember/Renderer/EditorCamera.h"
#include "Ember/Core/UUID.h"

#include <entt/entt.hpp>

class b2World;

namespace Ember
{
	class EMBER_API Entity; // Forward declaration

	class EMBER_API Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();

		void OnRuntimeStart();
		void OnRuntimePause();
		void OnRuntimeStop();

		void SetName(const std::string& name) { Name = name; }
		const std::string& GetName() const { return Name; }

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		std::string Name;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2World* m_PhysicsWorld = nullptr;

		entt::registry m_Registry{ };
		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;

	};
}