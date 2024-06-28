#pragma once

#include "Ember/Core.h"
#include "Ember/Events/Event.h"

#include "Ember/Core/Timestep.h"

#include <string>

namespace Ember
{
    class EMBER_API Layer
    {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent([[maybe_unused]] Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}