#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	EMBER_PROFILE_FUNCTION();
		
	m_CheckerboardTexture = Ember::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	EMBER_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Ember::Timestep ts)
{
	EMBER_PROFILE_FUNCTION();

	EMBER_CORE_INFO("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
	
	m_CameraController.OnUpdate(ts);

	Ember::Renderer2D::ResetStats();
	
	{
		EMBER_PROFILE_SCOPE("Clear Screen");

		Ember::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Ember::RenderCommand::Clear();
	}

	{
		EMBER_PROFILE_SCOPE("Render Scene");

		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Ember::Renderer2D::DrawQuad({1.5f, -0.5f}, {0.5f, 0.75f}, glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Ember::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_SquareColor);
		Ember::Renderer2D::DrawQuad({0.0f, 0.0f, -0.99f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
		Ember::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.1f}, {1.0f, 1.0f}, glm::radians(45.0f), m_SquareColor);
		Ember::Renderer2D::DrawRotatedQuad({0.0f, 0.0f, 0.1f}, {1.0f, 1.0f}, glm::radians(rotation), m_CheckerboardTexture, 100.0f);
		// Ember::Renderer2D::DrawRotatedQuad({0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(45.0f), m_SquareColor);
		
		Ember::Renderer2D::EndScene();

		// Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());

		// for(float y = -5.0; y < 5.0; y += 0.1f)
		// {
		// 	for(float x = -5.0; x < 5.0; x += 0.1f)
		// 	{
		// 		glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
		// 		Ember::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
		// 	}
		// }

		// Ember::Renderer2D::EndScene();

	}
}

void Sandbox2D::OnEvent(Ember::Event &e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	EMBER_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	Ember::Renderer2D::Statistics stats = Ember::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
