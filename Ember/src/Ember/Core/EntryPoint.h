#pragma once
#include "Ember/Core/Base.h"
#include "Ember/Core/Application.h"
#include "Ember/Core/Log.h"
#include "Ember/Debug/Instrumentor.h"
#include "Ember/Server/Server.h"

#include <thread>

	extern Ember::Application* Ember::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Ember::Log::Init();

	// Starting the server in a separate thread
	Ember::Server server;
	std::thread serverThread([&server]() {
		server.Start(8080);
	});

	EMBER_PROFILE_BEGIN_SESSION("Startup", "EmberProfile-Startup.json");
	auto app = Ember::CreateApplication({ argc, argv });
	EMBER_PROFILE_END_SESSION();

	EMBER_PROFILE_BEGIN_SESSION("Runtime", "EmberProfile-Runtime.json");
	app->Run();
	server.SetRunning(false);
	EMBER_PROFILE_END_SESSION();

	EMBER_PROFILE_BEGIN_SESSION("Shutdown", "EmberProfile-Shutdown.json");
	delete app;
	EMBER_PROFILE_END_SESSION();

	// Join the server thread before exiting
	serverThread.join();

	return 0;
}
