#pragma once

#include "Ember/Core/Base.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Core log macros
#define EMBER_CORE_TRACE(...)		::Ember::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EMBER_CORE_INFO(...)		::Ember::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EMBER_CORE_WARN(...)		::Ember::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EMBER_CORE_ERROR(...)		::Ember::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EMBER_CORE_CRITICAL(...)	::Ember::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EMBER_TRACE(...)			::Ember::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EMBER_INFO(...)				::Ember::Log::GetClientLogger()->info(__VA_ARGS__)
#define EMBER_WARN(...)				::Ember::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EMBER_ERROR(...)			::Ember::Log::GetClientLogger()->error(__VA_ARGS__)
#define EMBER_CRITICAL(...)			::Ember::Log::GetClientLogger()->critical(__VA_ARGS__)
