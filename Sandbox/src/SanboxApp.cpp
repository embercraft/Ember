#include "Ember.h"
#include "Ember/Core/EntryPoint.h"

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Ember::Application
{
	public:
	Sandbox()
		: Application("Sandbox", Ember::ApplicationCommandLineArgs(), 1920, 1080)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Ember::Application* Ember::CreateApplication(ApplicationCommandLineArgs args)
{
	return new Sandbox();
}
