#include "Emberpch.h"
#include "Ember/Core/Application.h"

#include "Ember/Core/Log.h"
#include "Ember/Renderer/Renderer.h"
#include "Ember/Core/Timestep.h"

#include <GLFW/glfw3.h>

namespace Ember {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, ApplicationCommandLineArgs args)
		: m_CommandLineArgs(args)
	{
		EMBER_PROFILE_FUNCTION();

		EMBER_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(EMBER_BIND_EVENT_FN(Application::OnEvent));
		// m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		EMBER_PROFILE_FUNCTION();
		
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		EMBER_PROFILE_FUNCTION();
		
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		EMBER_PROFILE_FUNCTION();
		
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

    void Application::Close()
    {
		m_Running = false;
    }

    void Application::OnEvent(Event &e)
    {
		EMBER_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EMBER_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(EMBER_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<WindowMinimizedEvent>(EMBER_BIND_EVENT_FN(Application::OnWindowMinimized));
		dispatcher.Dispatch<WindowRestoredEvent>(EMBER_BIND_EVENT_FN(Application::OnWindowRestored));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
			{
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		EMBER_PROFILE_FUNCTION();

		while (m_Running)
		{
			EMBER_PROFILE_SCOPE("RunLoop");

			double time = (float)glfwGetTime();
			Timestep timestep = (time - m_LastFrameTime);
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		EMBER_PROFILE_FUNCTION();

		EMBER_CORE_TRACE("WindowResizeEvent ({0}, {1})", e.GetWidth(), e.GetHeight());
		
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnWindowMinimized(WindowMinimizedEvent& e)
	{
		EMBER_PROFILE_FUNCTION();
		
		m_Minimized = true;
		return false;
	}

	bool Application::OnWindowRestored(WindowRestoredEvent& e)
	{
		EMBER_PROFILE_FUNCTION();
		
		m_Minimized = false;
		return false;
	}

}