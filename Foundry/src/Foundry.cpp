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
			server(CreateRef<Server>())
		{
			EditorLayer* editorLayer = new EditorLayer();
			ServerFactory::CreateAndStartServer(serverThread, server, "CustomListener", "EditorLayer", editorLayer, 8080);
			PushLayer(editorLayer);
		}

		~Foundry()
		{
			ServerFactory::StopServer(server, serverThread);
		}

	private:

		Ref<Server> server;
		std::thread serverThread;
	};

	Application *CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Foundry();
	}

}
