#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Layer.h"

namespace Ember
{

	class EMBER_API Listener
	{
	public:
		virtual ~Listener() = default;

		virtual void HandleClient(int client_socket) = 0;

		virtual void SetContext(Layer *context) = 0;
	};

	// To be defined in CLIENT
	Listener *CreateListener();

}
