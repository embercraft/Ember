#pragma once

#if defined(EMBER_PLATFORM_LINUX)

    extern Ember::Application* Ember::CreateApplication();

    int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
    {
        Ember::Log::Init();
        EMBER_CORE_TRACE("Initialized Log!");
        EMBER_INFO("Initialized Log!");
        auto app = Ember::CreateApplication();
        app->Run();
        EMBER_ERROR("Application Closed");
        delete app;
        return 0;
    }

#endif