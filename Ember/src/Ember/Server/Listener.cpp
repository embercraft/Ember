#include "Emberpch.h"
#include "Ember/Server/Listener.h"
#include "Ember/Core/Log.h"

#include <iostream>
#include <unistd.h>
#include <cstring>

namespace Ember
{
	namespace Listener
	{
		void HandleClient(int client_socket)
		{
			char buffer[1024] = {0};
			ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer));
			if (bytes_read > 0)
			{
				EMBER_CORE_INFO("Received: {0}", buffer);
			}
			else
			{
				EMBER_CORE_ERROR("Read error");
			}

			// Close the client socket
			close(client_socket);
		}
	}
}
