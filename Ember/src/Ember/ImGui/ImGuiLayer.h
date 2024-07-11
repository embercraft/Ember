#pragma once

#include "Ember/Core/Layer.h"

#include "Ember/Events/ApplicationEvent.h"
#include "Ember/Events/KeyEvent.h"
#include "Ember/Events/MouseEvent.h"

namespace Ember {

	class EMBER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

	private:
		[[maybe_unused]] float m_Time = 0.0f;
	};

}