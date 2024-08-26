#pragma once

#include "Ember/Core/Base.h"

#include <atomic>
#include <cstdint>

namespace Ember
{
	class EMBER_API Server
	{
	public:
		Server();
		~Server() = default;

		void Start(uint16_t port);
		void Stop(std::thread& serverThread);
		bool IsRunning() const;
		void SetRunning(bool running) { m_Running = running; }
		bool GetRunning() const { return m_Running; }
		uint16_t GetPort() const { return m_Port; }

	private:
		uint16_t m_Port;
		std::atomic<bool> m_Running;	
	};
}
