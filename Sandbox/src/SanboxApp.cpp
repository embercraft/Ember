#include "Ember.h"

class ExampleLayer : public Ember::Layer
{
	public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
	}

	void OnEvent(Ember::Event& event) override
	{
		if (event.GetEventType() == Ember::EventType::KeyPressed)
		{
			Ember::KeyPressedEvent& e = (Ember::KeyPressedEvent&)event;
			EMBER_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Ember::Application
{
	public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new Sandbox();
}
