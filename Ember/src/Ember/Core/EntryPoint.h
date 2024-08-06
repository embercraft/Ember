#pragma once

#if defined(EMBER_PLATFORM_LINUX)

	extern Ember::Application* Ember::CreateApplication(ApplicationCommandLineArgs args);

	int main(int argc, char** argv)
	{
		Ember::Log::Init();

		EMBER_PROFILE_BEGIN_SESSION("Startup", "EmberProfile-Startup.json");
		auto app = Ember::CreateApplication({ argc, argv });
		EMBER_PROFILE_END_SESSION();

		EMBER_PROFILE_BEGIN_SESSION("Runtime", "EmberProfile-Runtime.json");
		app->Run();
		EMBER_PROFILE_END_SESSION();
		
		EMBER_PROFILE_BEGIN_SESSION("Shutdown", "EmberProfile-Shutdown.json");
		delete app;
		EMBER_PROFILE_END_SESSION();
	}

#endif