#pragma once

#include <memory>

#if defined(EMBER_PLATFORM_LINUX)
	#if defined(EMBER_BUILD_LIB) && defined(BUILD_SHARED_LIBS)
		// Export symbols in shared library build
		#define EMBER_API __attribute__((visibility("default")))
	#else
		// No special attribute needed for import or static library build
		#define EMBER_API
	#endif
#elif defined(EMBER_PLATFORM_WINDOWS)
	#pragma message("Might not build, testing only on Linux")
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

#define EMBER_ENABLE_ASSERTS

#ifdef EMBER_ENABLE_ASSERTS
	#ifdef EMBER_PLATFORM_LINUX
		#define EMBER_ASSERT(x, ...) { if(!(x)) { EMBER_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
		#define EMBER_CORE_ASSERT(x, ...) { if(!(x)) { EMBER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
	#elif defined(EMBER_PLATFORM_WINDOWS)
		#define EMBER_ASSERT(x, ...) { if(!(x)) { EMBER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define EMBER_CORE_ASSERT(x, ...) { if(!(x)) { EMBER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#endif
#else
	#define EMBER_ASSERT(x, ...)
	#define EMBER_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

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