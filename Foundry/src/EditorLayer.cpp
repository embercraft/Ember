#include "EditorLayer.h"

#include "Ember/Scene/SceneSerializer.h"
#include "Ember/Utils/PlatformUtils.h"

#include "Ember/Math/Math.h"

#include <ImGui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ember
{

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
	{
	}

	void EditorLayer::OnAttach()
	{
		EMBER_PROFILE_FUNCTION();
			
		m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");
		m_SpriteSheet = Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");
		m_TextureStairs = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
		m_TextureBarrel = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128, 128 });
		m_TextureTree = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->SetName("Untitled Scene");

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
	}

	void EditorLayer::OnDetach()
	{
		EMBER_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		EMBER_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// EMBER_CORE_INFO("Delta time: {0}ms ({1} fps)", ts.GetMilliseconds(), 1.0f / ts.GetSeconds());

		if(m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
			m_EditorCamera.OnUpdate(ts);
		}

		// Render
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		RenderCommand::Clear();

		// Clear our entity ID attachment to -1
		m_Framebuffer->ClearAttachment(1, -1);

		// Update Scene
		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

		auto[mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			m_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, m_ActiveScene.get());
		}

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		EMBER_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if(ImGui::MenuItem("New", "Ctrl+N"))
				{
					NewScene();
				}

				if(ImGui::MenuItem("Open...", "Ctrl+O"))
				{
					OpenScene();
				}

				if(ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
				{
					SaveSceneAs();
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "Alt+F4"))
				{
					Application::Get().Close();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Theme"))
			{
				if(ImGui::MenuItem("Dark Theme"))
				{
					ImGuiLayer* imguiLayer = Application::Get().GetImGuiLayer();
					imguiLayer->SetDarkTheme();
				}
				
				if(ImGui::MenuItem("Catpuccin Theme"))
				{
					ImGuiLayer* imguiLayer = Application::Get().GetImGuiLayer();
					imguiLayer->SetCatpuccinTheme();
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Classic Theme"))
				{
					ImGui::StyleColorsClassic();
				}

				if (ImGui::MenuItem("Classic Light Theme"))
				{
					ImGui::StyleColorsLight();
				}

				if (ImGui::MenuItem("Classic Dark Theme"))
				{
					ImGui::StyleColorsDark();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Stats");

		std::string name = "None";
		if(m_HoveredEntity)
		{
			name = m_HoveredEntity.GetComponent<TagComponent>().Tag;
		}
		ImGui::Text("Hovered Entity: %s", name.c_str());

		ImGui::Separator();

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { ViewportPanelSize.x, ViewportPanelSize.y };
		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		
		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if(selectedEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			
			ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

			// Camera

			// Runtime Camera from entity
			// auto CameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			// const auto& camera = CameraEntity.GetComponent<CameraComponent>().Camera;
			// const glm::mat4& cameraProjection = camera.GetProjectionMatrix();
			// glm::mat4 cameraView = glm::inverse(CameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Editor Camera

			const glm::mat4& cameraProjection = m_EditorCamera.GetProjectionMatrix();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

			// Entity Transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(KeyCode::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if(m_GizmoType == ImGuizmo::OPERATION::ROTATE)
			{
				snapValue = 45.0f;
			}

			float snapValues[3] = {snapValue, snapValue, snapValue};

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

			if(ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}

		}
		
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event &e)
	{
		m_CameraController.OnEvent(e);
		m_EditorCamera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(EMBER_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(EMBER_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		if(e.GetRepeatCount() > 0)
		{
			return false;
		}

		bool control = Input::IsKeyPressed(KeyCode::LeftControl) || Input::IsKeyPressed(KeyCode::RightControl);
		bool shift = Input::IsKeyPressed(KeyCode::LeftShift) || Input::IsKeyPressed(KeyCode::RightShift);
		bool alt = Input::IsKeyPressed(KeyCode::LeftAlt);
		
		switch (e.GetKeyCode())
		{
			// File Operations
			case Key::N:
			{
				if(control)
				{
					NewScene();
				}
				break;
			}

			case Key::O:
			{
				if(control)
				{
					OpenScene();
				}
				break;
			}

			case Key::S:
			{
				if(control && shift)
				{
					SaveSceneAs();
				}
				break;
			}

			case Key::F4:
			{
				if(alt)
				{
					Application::Get().Close();
				}
				break;
			}

			// Gizmo Controls
			case Key::Q:
			{
				if (!ImGuizmo::IsUsing())
				{
					m_GizmoType = -1;
				}
				break;
			}

			case Key::W:
			{
				if(!ImGuizmo::IsUsing())
				{
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				}
				break;
			}

			case Key::E:
			{
				if(!ImGuizmo::IsUsing())
				{
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				}
				break;
			}

			case Key::R:
			{
				if(!ImGuizmo::IsUsing())
				{
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				}
				break;
			}

		}

		return false;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent &e)
	{
		if(e.GetMouseButton() == Mouse::ButtonLeft)
		{
			if(m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(KeyCode::LeftAlt) && !Input::IsKeyPressed(KeyCode::LeftControl))
			{
				m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
				m_GizmoType = -1;
			}
		}

		return false;
	}

    void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::optional<std::string> filePath = FileDialog::OpenFile("Ember Scene | *.ember");
		if(filePath)
		{
			std::string path = *filePath;
			if(path.length() >= 6 && path.substr(path.length() - 6) == ".ember")
			{
				m_ActiveScene = CreateRef<Scene>();
				m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_SceneHierarchyPanel.SetContext(m_ActiveScene);

				SceneSerializer serializer(m_ActiveScene);
				serializer.Deserialize(path);
			}
			else
			{
				std::string fileName = *filePath;
				std::size_t lastSlash = fileName.find_last_of("/");
				if (lastSlash != std::string::npos)
				{
					fileName = fileName.substr(lastSlash + 1);
				}
				EMBER_ERROR("Failed to open scene file: {0}, Only .ember files can be loaded.", fileName);
			}
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::optional<std::string> filePath = FileDialog::SaveFile("Ember Scene | *.ember");
		if(filePath)
		{
			std::string path = *filePath;
			
			// Check if the file has the .ember extension, if not, add it
			if(path.substr(path.find_last_of(".") + 1) != "ember")
			{
				path += ".ember";
			}

			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(path);
		}
	}

}
