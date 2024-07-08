#include "Emberpch.h"

#include "Ember/Renderer/Renderer2D.h"
#include "Ember/Renderer/VertexArray.h"
#include "Ember/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"

namespace Ember{

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		// TODO: add tiling factor
	};

	struct Renderer2DData
	{
		// max data per draw call
		const uint32_t MaxQuads = 10000; // TODO: test this & make it dynamic
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		EMBER_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for(uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);

		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t WhiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		EMBER_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera &camera)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		EMBER_PROFILE_FUNCTION();

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

    void Renderer2D::Flush()
    {
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4& color)
	{
		EMBER_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = {position.x, position.y, position.z};
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position = {position.x + size.x, position.y, position.z};
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position = {position.x + size.x, position.y + size.y, position.z};
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position = {position.x, position.y + size.y, position.z};
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
		
		// s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);

		// s_Data.WhiteTexture->Bind();

		// // Create a transformation matrix
		// glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		// s_Data.TextureShader->SetMat4("u_Transform", transform);

		// s_Data.QuadVertexArray->Bind();
		// RenderCommand::DrawIndexed(s_Data.QuadVertexArray);	
	}

	void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const float& rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const float& rotation, const glm::vec4& color)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);

		s_Data.WhiteTexture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const float& rotation, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const float& rotation, const Ref<Texture2D> &texture, const float& tilingFactor, const glm::vec4& tintColor)
	{
		EMBER_PROFILE_FUNCTION();
		
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind();

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

}
