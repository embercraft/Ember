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
	
	m_CameraController.OnUpdate(ts);
	
	{
		EMBER_PROFILE_SCOPE("Clear Screen");

		Ember::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Ember::RenderCommand::Clear();
	}

	Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Ember::Renderer2D::DrawQuad({1.5f, -0.5f}, {0.5f, 0.75f}, glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
	Ember::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_SquareColor);
	Ember::Renderer2D::DrawQuad({-5.0f, -5.0f, -0.99f}, {10.0f, 10.0f}, m_CheckerboardTexture, 10.0f, {122.0/255.0, 27.0/255.0, 160.0/255.0, 1.0});
	// Ember::Renderer2D::DrawRotatedQuad({0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(45.0f), m_SquareColor);
	
	Ember::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Ember::Event &e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	EMBER_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
