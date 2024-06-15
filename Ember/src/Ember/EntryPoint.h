#pragma once

#if defined(EMBER_PLATFORM_LINUX)

    extern Ember::Application* Ember::CreateApplication();

    int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
    {
        Ember::Log::Init();
        EMBER_CORE_TRACE("Initialized Log!");
        EMBER_INFO("Initialized Log!");
        auto app = Ember::CreateApplication();
        EMBER_WARN("Initialized Log!");
        app->Run();                         // Infinite loop
        EMBER_ERROR("Initialized Log!");     // This line will never be reached
        delete app;
        return 0;
    }

#endif