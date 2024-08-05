#include "Ember.h"
#include "Ember/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Ember
{

	class Foundry : public Application
	{
	public:
		Foundry()
			: Application("Foundry")
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
