#pragma once

#if defined(EMBER_PLATFORM_LINUX)
    #if defined(EMBER_BUILD_SHARED)
        #define EMBER_API __attribute__((visibility("default")))
    #else
        #define EMBER_API 
    #endif
#elif defined(EMBER_PLATFORM_WINDOWS)
    #if defined(EMBER_BUILD_SHARED)
        #define EMBER_API __declspec(dllexport)
    #else
        #define EMBER_API 
    #endif
#endif

#define BIT(x) (1 << x)