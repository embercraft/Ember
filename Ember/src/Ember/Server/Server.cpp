#include "Emberpch.h"
#include "Ember/Server/Server.h"
#include "Ember/Core/Log.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <chrono>
#include <thread>

namespace Ember
{

	Server::Server()
		: m_Port(0), m_Running(false), m_ServerFd(-1), m_Listener(nullptr)
	{
		if (socketpair(AF_UNIX, SOCK_STREAM, 0, m_SignalFd) < 0)
		{
			EMBER_CORE_ERROR("Socketpair creation failed: {0}", strerror(errno));
			EMBER_ASSERT(false);
		}
	}

	Server::~Server()
	{
		if (m_ServerFd != -1)
		{
			close(m_ServerFd);
		}
		close(m_SignalFd[0]);
		close(m_SignalFd[1]);
	}

	void Server::Start(uint16_t port)
	{
		m_Port = port;
		m_Running = true;

		m_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
		if (m_ServerFd < 0)
		{
			EMBER_CORE_ERROR("Socket creation failed: {0}", strerror(errno));
			EMBER_ASSERT(false);
		}

		int optval = 1;
		setsockopt(m_ServerFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

		int flags = fcntl(m_ServerFd, F_GETFL, 0);
		fcntl(m_ServerFd, F_SETFL, flags | O_NONBLOCK);

		sockaddr_in address{};
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);

		if (bind(m_ServerFd, (struct sockaddr *)&address, sizeof(address)) < 0)
		{
			EMBER_CORE_ERROR("Bind failed: {0}", strerror(errno));
			close(m_ServerFd);
			EMBER_ASSERT(false);
		}

		if (listen(m_ServerFd, 3) < 0)
		{
			EMBER_CORE_ERROR("Listen failed: {0}", strerror(errno));
			close(m_ServerFd);
			EMBER_ASSERT(false);
		}

		EMBER_CORE_INFO("Server started on port {0}", port);

		fd_set read_fds;
		int max_fd = std::max(m_ServerFd, m_SignalFd[0]) + 1;

		while (m_Running)
		{
			FD_ZERO(&read_fds);
			FD_SET(m_ServerFd, &read_fds);
			FD_SET(m_SignalFd[0], &read_fds);

			int activity = select(max_fd, &read_fds, nullptr, nullptr, nullptr);

			if (activity < 0 && errno != EINTR)
			{
				EMBER_CORE_ERROR("Select error: {0}", strerror(errno));
				break;
			}

			if (FD_ISSET(m_SignalFd[0], &read_fds))
			{
				char buffer[1];
				read(m_SignalFd[0], buffer, 1);
				break;
			}

			if (FD_ISSET(m_ServerFd, &read_fds))
			{
				int client_socket = accept(m_ServerFd, nullptr, nullptr);
				if (client_socket < 0)
				{
					if (errno != EAGAIN && errno != EWOULDBLOCK)
					{
						EMBER_CORE_ERROR("Accept failed: {0}", strerror(errno));
					}
					continue;
				}

				if (m_Listener)
					m_Listener->HandleClient(client_socket);
				else
					EMBER_CORE_ERROR("No Listener set to handle client socket {0}", client_socket);
			}
		}

		close(m_ServerFd);
		m_ServerFd = -1;
	}

	void Server::Stop()
	{
		if (m_Running)
		{
			m_Running = false;
			char buffer[1] = {0};
			write(m_SignalFd[1], buffer, 1);
		}
	}

	bool Server::IsRunning() const
	{
		return m_Running;
	}

	void ServerFactory::CreateAndStartServer(std::thread &serverThread, Ref<Server> &server, const std::string &listenerType, const std::string &contextKey, ListenerContext *contextObject, uint16_t port)
	{
		if (server && server->IsRunning())
		{
			EMBER_WARN("Server is already running on port {}", server->GetPort());
			return;
		}

		server = CreateRef<Server>();

		if (port < 1024 || port > 65535)
		{
			throw std::invalid_argument("Invalid port number");
		}

		serverThread = std::thread([server, port, contextObject,
									listenerType = std::string(listenerType),
									contextKey = std::string(contextKey)]()
								   {
		try {
			auto listener = ListenerFactory::Instance().CreateListener(listenerType);
			if (!listener) {
				throw std::runtime_error("Failed to create listener of type: " + listenerType);
			}

			if (contextObject) {
				listener->SetContext(contextKey, contextObject);
			}

			server->SetListener(listener.get());
			server->Start(port);
		} catch (const std::exception& e) {
			EMBER_ERROR("Server thread error: {}", e.what());
			server->SetRunning(false);
		} });
	}

	void ServerFactory::StopServer(Ref<Server> &server, std::thread &serverThread)
	{
		if (server && server->IsRunning())
		{
			server->Stop();
			if (serverThread.joinable())
			{
				serverThread.join();
			}
			EMBER_CORE_INFO("Server stopped on port {}", server->GetPort());
		}
		else
		{
			EMBER_CORE_WARN("Server is not running or thread is not joinable");
		}
	}
}
