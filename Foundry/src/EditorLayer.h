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
		void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& filePath);
		void SaveScene();
		void SaveSceneAs();
		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnDuplicateEntity();

		void OnSceneEdit();
		void OnScenePlay();
		void OnSceneStop();
		void OnSceneSimulate();
		void OnScenePause();

		/*
		OnScenePlay -> start runtime,
		OnScenePause -> pause runtime,
		OnSceneStop -> stop and delete runtime,
		OnSceneReset -> stop runtime and reset the scene
		*/

		// UI Panels
		void UI_Toolbar();

	private:
		OrthographicCameraController m_CameraController;

		Ref<Shader> m_FlatColorShader;
		Ref<VertexArray> m_SquareVA;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene = nullptr;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		Entity m_HoveredEntity;

		bool m_PrimaryCamera = true;
		bool m_FPS = false;

		EditorCamera m_EditorCamera;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		enum class SceneState
		{
			Edit = 0,
			Play = 1,
			Pause = 2,
			Stop = 3,
			Simulate = 4
		};

		SceneState m_SceneState = SceneState::Edit;

		Ref<Texture2D> m_IconPlay, m_IconStop;
	};

}
