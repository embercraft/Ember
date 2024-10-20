#include "Ember.h"
#include "Ember/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Ember
{

	class Foundry : public Application
	{
	public:
		Foundry()
			: Application("Foundry", ApplicationCommandLineArgs(), 1920, 1080, "Resources/Icons/Logo/Foundry.png")//, 1920, 1080, ApplicationCommandLineArgs())
		{
			PushLayer(new EditorLayer());
		}

		~Foundry()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Foundry();
	}

}
