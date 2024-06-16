#pragma once

#if defined(EMBER_PLATFORM_LINUX)
    #if defined(EMBER_BUILD_LIB) && defined(BUILD_SHARED_LIBS)
        // Export symbols in shared library build
        #define EMBER_API __attribute__((visibility("default")))
    #else
        // No special attribute needed for import or static library build
        #define EMBER_API
    #endif
#elif defined(EMBER_PLATFORM_WINDOWS)
    #if defined(EMBER_BUILD_LIB) && defined(BUILD_SHARED_LIBS)
        // Export symbols in shared library build
        #define EMBER_API __declspec(dllexport)
    #elif defined(BUILD_SHARED_LIBS)
        // Import symbols from shared library
        #define EMBER_API __declspec(dllimport)
    #else
        // No special attribute needed for static library build
        #define EMBER_API
    #endif
#else
    // Unsupported platform
    #error "Unsupported platform"
#endif

#ifdef EMBER_ENABLE_ASSERTS
    #ifdef _WIN32
        #define EMBER_ASSERT(x, ...) { if(!(x)) { EMBER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
        #define EMBER_CORE_ASSERT(x, ...) { if(!(x)) { EMBER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #elif defined(EMBER_PLATFORM_LINUX)
            #define EMBER_ASSERT(x, ...) { if(!(x)) { EMBER_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
            #define EMBER_CORE_ASSERT(x, ...) { if(!(x)) { EMBER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
    #endif
#else
    #define EMBER_ASSERT(x, ...)
    #define EMBER_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
