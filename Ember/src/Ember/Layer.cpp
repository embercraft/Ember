#include "Emberpch.h"

#include "Ember/Layer.h"

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