#include "Emberpch.h"

#include "Ember/Core/Layer.h"

namespace Ember
{
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Layer::~Layer()
	{
	}
}