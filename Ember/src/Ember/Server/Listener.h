#pragma once

#include "Ember/Core/Base.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

namespace Ember
{

	struct ListenerContext
	{
		virtual ~ListenerContext() = default;
	};

	class EMBER_API Listener
	{
	public:
		virtual ~Listener() = default;

		virtual void HandleClient(int client_socket) = 0;

		// Set context with a key to distinguish between different contexts
		virtual void SetContext(const std::string &key, ListenerContext *context) = 0;

		// Get a specific context
		virtual ListenerContext *GetContext(const std::string &key) const = 0;
	};

	// Factory registry for creating listeners
	class ListenerFactory
	{
	public:
		using CreatorFunc = std::function<Scope<Listener>()>;

		static ListenerFactory &Instance()
		{
			static ListenerFactory instance;
			return instance;
		}

		void RegisterListener(const std::string &type, CreatorFunc creator)
		{
			m_Creators[type] = std::move(creator);
		}

		Scope<Listener> CreateListener(const std::string &type)
		{
			auto it = m_Creators.find(type);
			if (it != m_Creators.end())
				return it->second();
			return nullptr;
		}

	private:
		std::unordered_map<std::string, CreatorFunc> m_Creators;
	};

#define REGISTER_LISTENER_TYPE(TYPE)             \
	namespace                                    \
	{                                            \
		const bool TYPE##_registered = [] { \
			ListenerFactory::Instance().RegisterListener(#TYPE, [] { return std::make_unique<TYPE>(); });\
			return true; }(); \
	}

}
