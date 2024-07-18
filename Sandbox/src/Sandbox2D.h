#pragma once

#include "Ember.h"

#include <ImGui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public Ember::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Ember::Timestep ts) override;
	void OnEvent(Ember::Event& e) override;
	virtual void OnImGuiRender() override;


private:
	Ember::OrthographicCameraController m_CameraController;

	Ember::Ref<Ember::Shader> m_FlatColorShader;
	Ember::Ref<Ember::VertexArray> m_SquareVA;

	Ember::Ref<Ember::Texture2D> m_CheckerboardTexture;
	Ember::Ref<Ember::Texture2D> m_SpriteSheet;
	Ember::Ref<Ember::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

};