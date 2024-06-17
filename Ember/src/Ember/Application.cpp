#include "Emberpch.h"
#include "Application.h"

#include "Ember/Log.h"

#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Ember
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

    void Application::OnEvent(Event &e)
    {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		EMBER_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		// Get GLFW version information
    	int major, minor, revision;
    	glfwGetVersion(&major, &minor, &revision);

    	// Print GLFW version
    	EMBER_CORE_INFO("GLFW version: {0}.{1}.{2}", major, minor, revision);
        
		while(m_Running)
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();

			m_Window->OnUpdate();
		}
	}

	bool Application::onWindowClose([[maybe_unused]] WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}
}