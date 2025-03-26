#include "Ember.h"
#include "Ember/Core/EntryPoint.h"
#include "Ember/Server/Server.h"

#include "EditorLayer.h"

namespace Ember
{

	class Foundry : public Application
	{
	public:
		Foundry()
			: Application("Foundry", ApplicationCommandLineArgs(), 1920, 1080, "Resources/Icons/Logo/Foundry.png"),
			server(CreateScope<Server>())
		{
			EditorLayer* editorLayer = new EditorLayer();
			serverStart(*editorLayer);
			PushLayer(editorLayer);
		}

		~Foundry()
		{
			serverStop();
		}

	private:
		void serverStart(EditorLayer& editorLayer)
		{
			serverThread = std::thread([this, &editorLayer]() {
				auto listener = CreateListener();
				listener->SetContext(&editorLayer);
				server->SetListener(listener);
				server->Start(8080);
			});
		}

		void serverStop()
		{
			server->Stop(serverThread);
		}

		Scope<Server> server;
		std::thread serverThread;
	};

	Application *CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Foundry();
	}

}
