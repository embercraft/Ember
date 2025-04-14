#include "Ember.h"
#include "EditorLayer.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>

namespace Ember
{

	class CustomListener : public Listener
	{
	public:
		void HandleClient(int client_socket) override
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

			// Trim whitespace
			command.erase(0, command.find_first_not_of(" \t\n\r"));
			command.erase(command.find_last_not_of(" \t\n\r") + 1);

			auto *editorLayer = dynamic_cast<EditorLayer *>(GetContext("EditorLayer"));
			if (!editorLayer)
			{
				EMBER_ERROR("EditorLayer context not set!");
				close(client_socket);
				return;
			}

			// Define command handlers
			static const std::unordered_map<std::string, std::function<void(EditorLayer *, const std::string &)>> commandHandlers = {
				{"flush", [](EditorLayer *layer, const std::string &) {
						EMBER_INFO("Flushing the scene...");
						layer->NewScene();
					}},
				{"load", [](EditorLayer *layer, const std::string &arg) {
						EMBER_INFO("Loading scene: {0}", arg);
						layer->LoadScene(arg);
					}},
				{"fload", [](EditorLayer *layer, const std::string &arg) {
						EMBER_INFO("Flushing current scene & Loading scene: {0}", arg);
						layer->FlushAndLoadScene(arg);
					}},
				{"log", [](EditorLayer *, const std::string &arg) {
						EMBER_INFO("Logging message: {0}", arg);
					}}
			};

			// Process command
			size_t spacePos = command.find(' ');
			std::string commandName = (spacePos == std::string::npos) ? command : command.substr(0, spacePos);
			std::string commandArg = (spacePos == std::string::npos) ? "" : command.substr(spacePos + 1);

			auto it = commandHandlers.find(commandName);
			if (it != commandHandlers.end())
			{
				it->second(editorLayer, commandArg);
			}
			else
			{
				EMBER_WARN("Unknown command: {0}", command);
			}

			close(client_socket);
		}

		void SetContext(const std::string &key, ListenerContext *context) override
		{
			m_Contexts[key] = context;
		}

		ListenerContext *GetContext(const std::string &key) const override
		{
			auto it = m_Contexts.find(key);
			return (it != m_Contexts.end()) ? it->second : nullptr;
		}

	private:
		std::unordered_map<std::string, ListenerContext *> m_Contexts;
	};

	// Register the CustomListener type with the ListenerFactory
	REGISTER_LISTENER_TYPE(CustomListener);

}
