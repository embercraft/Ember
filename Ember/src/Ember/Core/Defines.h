#pragma once

#define EMBER_PROFILE 0
#define EMBER_ENABLE_ASSERTS 1

// check build type for clang and gcc
#if defined(__clang__)
	#define EMBER_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	#define EMBER_COMPILER_GCC
#endif

// check if built in release or debug mode
#if defined(NDEBUG)
	#define EMBER_RELEASE
#else
	#define EMBER_DEBUG
#endif
