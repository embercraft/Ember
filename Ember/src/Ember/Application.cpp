#include "Application.h"

#include "Ember/Events/ApplicationEvent.h"
#include "Ember/Log.h"

namespace Ember
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
        WindowResizeEvent e(1280, 720);
        EMBER_TRACE(e);
//        if (e.IsInCategory(EventCategoryApplication))
//        {
//            EMBER_TRACE(e);
//        }
//        if (e.IsInCategory(EventCategoryInput))
//        {
//            EMBER_TRACE(e);
//        }

		while (true);
	}
}