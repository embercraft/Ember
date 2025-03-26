#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Server/Listener.h"

#include <atomic>
#include <thread>

namespace Ember
{

	class EMBER_API Server
	{
	public:
		Server();
		~Server() = default;

		// Start the server on a specific port.
		void Start(uint16_t port);
		// Stop the server by joining the provided thread.
		void Stop(std::thread &serverThread);
		bool IsRunning() const;
		void SetRunning(bool running) { m_Running = running; }
		uint16_t GetPort() const { return m_Port; }

		// Set the Listener instance.
		void SetListener(Listener *listener) { m_Listener = listener; }

	private:
		uint16_t m_Port;
		Listener *m_Listener = nullptr;
		std::atomic<bool> m_Running;
	};

}
