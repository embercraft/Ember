#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	EMBER_PROFILE_FUNCTION();
		
	m_CheckerboardTexture = Ember::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Ember::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");
	m_TextureStairs = Ember::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureBarrel = Ember::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128, 128 });
	m_TextureTree = Ember::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
}

void Sandbox2D::OnDetach()
{
	EMBER_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Ember::Timestep ts)
{
	EMBER_PROFILE_FUNCTION();

	EMBER_CORE_INFO("Delta time: {0}ms ({1} fps)", ts.GetMilliseconds(), 1.0f / ts.GetSeconds());
	
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

		Ember::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(45.0f), m_TextureStairs);
		Ember::Renderer2D::DrawRotatedQuad({1.5f, 0.0f, +0.1f}, {1.0f, 2.0f}, glm::radians(45.0f), m_TextureTree);
		
		Ember::Renderer2D::EndScene();
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
