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
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float& rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float& rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float& rotation, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float& rotation, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tintColor = glm::vec4(1.0f));
	};

}
