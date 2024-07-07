#include "Emberpch.h"

#include "Ember/Renderer/Renderer2D.h"
#include "Ember/Renderer/VertexArray.h"
#include "Ember/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"

namespace Ember{

	struct Renderer2DStorage
	{
		Ref<VertexArray> SquareVA;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Ref<Renderer2DStorage> s_Data;

	void Renderer2D::Init()
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data = CreateScope<Renderer2DStorage>();

		s_Data->SquareVA = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		s_Data->SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->SquareVA->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t WhiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		EMBER_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera &camera)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4& color)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);

		s_Data->WhiteTexture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->SquareVA->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVA);	
	}

	void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->SquareVA->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVA);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const float& rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const float& rotation, const glm::vec4& color)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);

		s_Data->WhiteTexture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->SquareVA->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVA);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const float& rotation, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const float& rotation, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->SquareVA->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVA);
	}

}
