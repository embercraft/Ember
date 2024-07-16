#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Scene/SceneCamera.h"
#include "Ember/Scene/ScriptableEntity.h"

#include <glm/glm.hpp>

namespace Ember
{

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}
		
		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}

		operator glm::vec4& () { return Color; }
		operator const glm::vec4& () const { return Color; }
		operator std::string ()
		{
			std::stringstream ss;
			ss << "r: " << Color.r << ", g: " << Color.g << ", b: " << Color.b << ", a: " << Color.a;
			return ss.str();
		}
		operator const std::string& () const
		{
			std::stringstream ss;
			ss << "r: " << Color.r << ", g: " << Color.g << ", b: " << Color.b << ", a: " << Color.a;
			return ss.str();
		}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: Move to scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstanciateScript)();
		void(*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstanciateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

}
