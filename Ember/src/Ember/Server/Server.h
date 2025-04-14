#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Server/Listener.h"

#include <atomic>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <unistd.h>

namespace Ember
{

	class EMBER_API Server
	{
	public:
		Server();
		~Server();

		void Start(uint16_t port);
		void Stop();
		bool IsRunning() const;
		void SetRunning(bool running) { m_Running = running; }
		uint16_t GetPort() const { return m_Port; }

		void SetListener(Listener *listener) { m_Listener = listener; }

	private:
		uint16_t m_Port;
		Listener *m_Listener;
		std::atomic<bool> m_Running;
		int m_ServerFd;
		int m_SignalFd[2];
	};

	class EMBER_API ServerFactory
	{
	public:
		static void CreateAndStartServer(std::thread &serverThread, Ref<Server> &server,
										 const std::string &listenerType, const std::string &contextKey,
										 ListenerContext *contextObject, uint16_t port = 8080);

		static void StopServer(Ref<Server> &server, std::thread &serverThread);
	};
}
