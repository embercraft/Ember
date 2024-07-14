#pragma once

#include "Ember/Core/Base.h"

#include "Ember/Core/Window.h"
#include "Ember/Core/LayerStack.h"
#include "Ember/Events/Event.h"
#include "Ember/Events/ApplicationEvent.h"

#include "Ember/Core/Timestep.h"

#include "Ember/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Ember
{
	class EMBER_API Application
	{

	public:
		
		Application(const std::string& name = "Ember App");
		
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowMinimized(WindowMinimizedEvent& e);
		bool OnWindowRestored(WindowRestoredEvent& e);
	
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
