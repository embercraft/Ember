#pragma once

#include "Ember.h"
#include "Panels/ScenehierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Ember/Renderer/EditorCamera.h"

#include <filesystem>

namespace Ember
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep ts) override;
		void OnEvent(Event &e) override;
		virtual void OnImGuiRender() override;

		void NewScene();
		void LoadScene(const std::filesystem::path &filePath);
		void FlushAndLoadScene(const std::filesystem::path &filePath);
		
		private:
		void OpenScene();
		void SaveSceneAs();
		bool OnKeyPressed(KeyPressedEvent &e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent &e);

	private:
		OrthographicCameraController m_CameraController;

		Ref<Shader> m_FlatColorShader;
		Ref<VertexArray> m_SquareVA;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		Entity m_HoveredEntity;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {0.0f, 0.0f};
		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
	};

}
