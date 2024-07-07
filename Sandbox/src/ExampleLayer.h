#pragma once 

#include "Ember.h"

class ExampleLayer : public Ember::Layer
{
	public:
	ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

	void OnUpdate(Ember::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ember::Event& event) override;
	
private:
	Ember::ShaderLibrary m_ShaderLibrary;
	Ember::Ref<Ember::Shader> m_Shader;
	Ember::Ref<Ember::VertexArray> m_VertexArray;

	Ember::Ref<Ember::Shader> m_FlatColorShader;
	Ember::Ref<Ember::VertexArray> m_SquareVA;

	Ember::Ref<Ember::Texture2D> m_Texture, m_Texture2;

	Ember::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};

};