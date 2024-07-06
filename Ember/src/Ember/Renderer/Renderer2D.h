#pragma once

#include "Ember/Core/Core.h"
#include "Ember/Renderer/OrthographicCamera.h"
#include "Ember/Renderer/RenderCommand.h"
#include "Ember/Renderer/Texture.h"

namespace Ember {

	class EMBER_API Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& rotation = { 0.0f, 0.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& rotation = { 0.0f, 0.0f });
		static void DrawTexture(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& rotation = { 0.0f, 0.0f });
		static void DrawTexture(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& rotation = { 0.0f, 0.0f });
	};

}
