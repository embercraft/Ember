#include "Emberpch.h"
#include "Ember/ImGui/ImGuiLayer.h"
#include "Ember/Core/Application.h"

#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>

#include <ImGuizmo/ImGuizmo.h>

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ember {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		EMBER_PROFILE_FUNCTION();
		
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	   // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	  // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		   // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		 // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/static/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/static/OpenSans-Regular.ttf", 18.0f);

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		EMBER_PROFILE_FUNCTION();
		
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

    void ImGuiLayer::OnEvent(Event &e)
    {
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
    }

    void ImGuiLayer::Begin()
    {
		EMBER_PROFILE_FUNCTION();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void ImGuiLayer::End()
	{
		EMBER_PROFILE_FUNCTION();
		
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetDarkTheme()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	void ImGuiLayer::SetCatpuccinTheme()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.13f, 0.14f, 0.22f, 1.0f };  // Slightly darker base

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.27f, 0.28f, 0.39f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.34f, 0.35f, 0.48f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.42f, 0.44f, 0.58f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.29f, 0.30f, 0.43f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.37f, 0.38f, 0.52f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.46f, 0.47f, 0.62f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.29f, 0.30f, 0.43f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.37f, 0.38f, 0.52f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.46f, 0.47f, 0.62f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.27f, 0.28f, 0.39f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.34f, 0.35f, 0.48f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.42f, 0.44f, 0.58f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.20f, 0.21f, 0.31f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.27f, 0.28f, 0.39f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.20f, 0.21f, 0.31f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.27f, 0.28f, 0.39f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.20f, 0.21f, 0.31f, 1.0f };

		// Accent colors
		colors[ImGuiCol_Text] = ImVec4{ 0.91f, 0.91f, 0.95f, 1.0f };  // Brighter text
		colors[ImGuiCol_TextSelectedBg] = ImVec4{ 0.79f, 0.75f, 1.00f, 0.35f };  // Vibrant lavender
		colors[ImGuiCol_CheckMark] = ImVec4{ 1.00f, 0.76f, 0.83f, 1.0f };  // Brighter pink
		colors[ImGuiCol_SliderGrab] = ImVec4{ 0.95f, 0.77f, 0.80f, 1.0f };  // Vibrant flamingo
		colors[ImGuiCol_SliderGrabActive] = ImVec4{ 1.00f, 0.76f, 0.83f, 1.0f };  // Brighter pink

		// Additional accent colors
		colors[ImGuiCol_BorderShadow] = ImVec4{ 0.00f, 0.00f, 0.00f, 0.00f };
		colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.13f, 0.14f, 0.22f, 1.0f };
		colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.42f, 0.44f, 0.58f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.50f, 0.52f, 0.67f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.58f, 0.60f, 0.76f, 1.0f };
		colors[ImGuiCol_PopupBg] = ImVec4{ 0.15f, 0.16f, 0.24f, 1.0f };
		colors[ImGuiCol_Border] = ImVec4{ 0.42f, 0.44f, 0.58f, 0.5f };
	}

}