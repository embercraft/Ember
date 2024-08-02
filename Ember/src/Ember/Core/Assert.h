#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Log.h"
#include <filesystem>

#if EMBER_ENABLE_ASSERTS
    #ifdef EMBER_PLATFORM_LINUX
        #include <signal.h>
        #define EMBER_DEBUGBREAK() raise(SIGTRAP)
        #define EMBER_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EMBER##type##ERROR(msg, __VA_ARGS__); EMBER_DEBUGBREAK(); } }
        #define EMBER_ASSERT_WITH_MSG(type, check, ...) EMBER_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
        #define EMBER_ASSERT_NO_MSG(type, check) EMBER_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EMBER_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
    #elif defined(EMBER_PLATFORM_WINDOWS)
        #define EMBER_DEBUGBREAK() __debugbreak()
        #define EMBER_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EMBER##type##ERROR(msg, __VA_ARGS__); EMBER_DEBUGBREAK(); } }
        #define EMBER_ASSERT_WITH_MSG(type, check, ...) EMBER_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
        #define EMBER_ASSERT_NO_MSG(type, check) EMBER_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EMBER_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
    #endif

    #define EMBER_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define EMBER_ASSERT_GET_MACRO(...) EMBER_EXPAND_MACRO( EMBER_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EMBER_ASSERT_WITH_MSG, EMBER_ASSERT_NO_MSG) )

    #define EMBER_ASSERT(...) EMBER_EXPAND_MACRO( EMBER_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define EMBER_CORE_ASSERT(...) EMBER_EXPAND_MACRO( EMBER_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define EMBER_ASSERT(...)
    #define EMBER_CORE_ASSERT(...)
#endif
