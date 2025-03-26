#pragma once

#include "Ember/Core/Base.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Ember
{

	class EMBER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#ifdef EMBER_DEBUG
	#define EMBER_CORE_TRACE(...)		::Ember::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define EMBER_CORE_INFO(...)		::Ember::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define EMBER_CORE_WARN(...)		::Ember::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define EMBER_CORE_ERROR(...)		::Ember::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define EMBER_CORE_CRITICAL(...)	::Ember::Log::GetCoreLogger()->critical(__VA_ARGS__)
#else
	#define EMBER_CORE_TRACE(...)
	#define EMBER_CORE_INFO(...)
	#define EMBER_CORE_WARN(...)
	#define EMBER_CORE_ERROR(...)
	#define EMBER_CORE_CRITICAL(...)
#endif

// Client log macros
#ifdef EMBER_DEBUG
	#define EMBER_TRACE(...)			::Ember::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define EMBER_INFO(...)				::Ember::Log::GetClientLogger()->info(__VA_ARGS__)
	#define EMBER_WARN(...)				::Ember::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define EMBER_ERROR(...)			::Ember::Log::GetClientLogger()->error(__VA_ARGS__)
	#define EMBER_CRITICAL(...)			::Ember::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define EMBER_TRACE(...)
	#define EMBER_INFO(...)
	#define EMBER_WARN(...)
	#define EMBER_ERROR(...)
	#define EMBER_CRITICAL(...)
#endif
