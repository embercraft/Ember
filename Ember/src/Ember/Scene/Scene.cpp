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

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>();
		auto& tag = entity.GetComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update Scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if(!nsc.Instance)
				{
					nsc.Instance = nsc.InstanciateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}
		
				nsc.Instance->OnUpdate(ts);
			});
		}
		

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<CameraComponent, TransformComponent>();
			for(auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if(camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}

		}

		if(mainCamera)
		{
			// Render 2D

			Renderer2D::BeginScene(mainCamera->GetProjectionMatrix(), cameraTransform);
			
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for(auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();

		}
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera &camera)
	{
		Renderer2D::BeginScene(camera);
			
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for(auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize camera's with non-FixedAspectRatio
		auto view = m_Registry.view<CameraComponent>();
		for(auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if(!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();

		for(auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);

			if(camera.Primary)
			{
				return Entity { entity, this};
			}
		}

		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

}