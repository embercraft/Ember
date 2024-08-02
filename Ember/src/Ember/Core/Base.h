#pragma once

#include "Ember/Core/Defines.h"

#include <memory>

#if defined(EMBER_PLATFORM_LINUX)
	#if defined(BUILD_SHARED_LIBS)
		// Export symbols in shared library build
		#define EMBER_API __attribute__((visibility("default")))
	#else
		// No special attribute needed for building/importing static library
		#define EMBER_API
	#endif
#elif defined(EMBER_PLATFORM_WINDOWS)
	#pragma message("Might not build, testing only on Linux")
	#if defined(BUILD_SHARED_LIBS)
		// Export symbols in shared library build
		#define EMBER_API __declspec(dllexport)
	#elif defined(BUILD_SHARED_LIBS)
		// Import symbols from shared library
		#define EMBER_API __declspec(dllimport)
	#else
		// No special attribute needed for building/importing static library
		#define EMBER_API
	#endif
#else
	// Unsupported platform
	#error "Unsupported platform"
#endif

#define BIT(x) (1 << x)
#define EMBER_EXPAND_MACRO(x) x
#define EMBER_STRINGIFY_MACRO(x) #x

#define EMBER_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Ember {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateRef(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}

#include "Ember/Core/Assert.h"
#include "Ember/Core/Log.h"
