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

	private:
		entt::registry m_Registry{ };
		friend class Entity;

	};
}