#include "Emberpch.h"
#include "Ember/Scene/Scene.h"
#include "Ember/Scene/Components.h"
#include "Ember/Scene/Entity.h"

#include "Ember/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Ember
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	// Entity Scene::CreateEntity(const std::string& name)
	// {
	// 	Entity entity = { m_Registry.create(), this };
	// 	entity.AddComponent<TransformComponent>();
	// 	auto& tag = entity.GetComponent<TagComponent>();
	// 	tag.Tag = name.empty() ? "Entity" : name;
	// 	return entity;
	// }

	Entity Scene::CreateEntity(const std::string& name)
	{
		entt::entity entityHandle = m_Registry.create();
		Entity entity(entityHandle, this);
		
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for(auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}

}