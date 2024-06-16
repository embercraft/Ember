#include "Emberpch.h"
#include "Application.h"

#include "Ember/Events/ApplicationEvent.h"
#include "Ember/Log.h"

#include <GLFW/glfw3.h>

namespace Ember
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
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
			// close window when close button is clicked
			if (m_Window->ShouldClose())
			{
				m_Running = false;
			}

			m_Window->OnUpdate();
		}
	}
}