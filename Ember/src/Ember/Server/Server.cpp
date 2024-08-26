#include "Ember/Server/Server.h"
#include "Ember/Server/Listener.h"
#include "Ember/Core/Log.h"

#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <errno.h>

namespace Ember
{
	Server::Server()
		: m_Port(0), m_Running(false)
	{
	}

	void Server::Start(uint16_t port)
	{
		m_Port = port;
		m_Running = true;

		int server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (server_fd < 0)
		{
			EMBER_CORE_ERROR("Socket creation failed: {0}", strerror(errno));
			EMBER_ASSERT(false);
		}

		// Set socket to non-blocking mode
		int flags = fcntl(server_fd, F_GETFL, 0);
		fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

		sockaddr_in address{};
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);

		if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
		{
			EMBER_CORE_ERROR("Bind failed: {0}", strerror(errno));
			close(server_fd);
			EMBER_ASSERT(false);
		}

		if (listen(server_fd, 3) < 0)
		{
			EMBER_CORE_ERROR("Listen failed: {0}", strerror(errno));
			close(server_fd);
			EMBER_ASSERT(false);
		}

		EMBER_CORE_INFO("Server started on port {0}", port);

		while (m_Running)
		{
			int client_socket = accept(server_fd, nullptr, nullptr);
			if (client_socket < 0)
			{
				if (errno == EAGAIN || errno == EWOULDBLOCK) // No clients to accept
				{
					// Sleep briefly to avoid busy waiting
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					continue;
				}

				if (!m_Running) break; // Exit loop if stopping
				EMBER_CORE_ERROR("Accept failed: {0}", strerror(errno));
				continue;
			}

			Listener::HandleClient(client_socket);
		}

		close(server_fd);
	}

	void Server::Stop(std::thread &serverThread)
	{
		
	}

	bool Server::IsRunning() const
	{
		return m_Running;
	}
}
