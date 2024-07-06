#include "Emberpch.h"

#include "Ember/Renderer/Renderer2D.h"
#include "Ember/Renderer/VertexArray.h"
#include "Ember/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ember{

	struct Renderer2DStorage
	{
		Ref<VertexArray> SquareVA;
		Ref<Shader> FlatColorShader;
	};

	static Ref<Renderer2DStorage> s_Data;

	void Renderer2D::Init()
	{
		s_Data = CreateScope<Renderer2DStorage>();

		s_Data->SquareVA = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
		});

		s_Data->SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->SquareVA->SetIndexBuffer(squareIB);

		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera &camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::Flush()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4& color, const glm::vec2& rotation)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4& color, const glm::vec2& rotation)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		// Create a transformation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)) * glm::rotate(glm::mat4(1.0f), rotation.x, {0.0f, 0.0f, 1.0f});
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		s_Data->SquareVA->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVA);	
	}

}
