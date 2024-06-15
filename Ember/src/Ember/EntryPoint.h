#pragma once

#if defined(EMBER_PLATFORM_LINUX)

    extern Ember::Application* Ember::CreateApplication();

    int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
    {
        Ember::Log::Init();
        EMBER_CORE_WARN("Initialized Log!");
        EMBER_INFO("Initialized Log!");
        auto app = Ember::CreateApplication();
        EMBER_INFO("Initialized Log!");
        app->Run();
        EMBER_INFO("Initialized Log!");
        delete app;
        return 0;
    }

#endif