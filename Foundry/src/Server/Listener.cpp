#include "Ember.h"
#include "EditorLayer.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

namespace Ember
{

	class CustomListener : public Listener
	{
	public:
		virtual void HandleClient(int client_socket) override
		{
			char buffer[1024] = {0};
			ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
			if (bytes_received < 0)
			{
				EMBER_CORE_ERROR("Failed to receive data from client on socket {0}", client_socket);
				EMBER_ERROR("Message dropped");
				close(client_socket);
				return;
			}
			buffer[bytes_received] = '\0';
			std::string command(buffer);

			command.erase(0, command.find_first_not_of(" \t\n\r"));
			command.erase(command.find_last_not_of(" \t\n\r") + 1);

			if (command == "flush")
			{
				EMBER_INFO("Flushing the scene...");
				m_EditorLayer->NewScene();
			}
			else if (command.rfind("load ", 0) == 0)
			{
				std::string scene = command.substr(5);
				EMBER_INFO("Loading scene: {0}", scene);
				m_EditorLayer->LoadScene(scene);
			}
			else if (command.rfind("fload ", 0) == 0)
			{
				std::string scene = command.substr(6);
				EMBER_INFO("Flushing current scene & Loading scene: {0}", scene);
				m_EditorLayer->FlushAndLoadScene(scene);
			}
			else if (command.rfind("log ", 0) == 0)
			{
				std::string message = command.substr(4);
				EMBER_INFO("Logging message: {0}", message);
			}
			else
			{
				EMBER_WARN("Unknown command: {0}", command);
			}

			close(client_socket);
		}

		void SetContext(Layer* context) override
		{
			m_EditorLayer = dynamic_cast<EditorLayer*>(context);
		}

	private:
		EditorLayer *m_EditorLayer;
	};

}

Ember::Listener *Ember::CreateListener()
{
	return new CustomListener();
}
