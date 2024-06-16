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

#define BIT(x) (1 << x)