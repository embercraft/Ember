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
	
	Ember::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	Ember::RenderCommand::Clear();
	
	Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Ember::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_SquareColor);
	Ember::Renderer2D::DrawQuad({0.5f, 0.5f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture);
	
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
