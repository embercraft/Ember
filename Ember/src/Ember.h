#pragma once

// For use by Ember applications
#include "Ember/Core/Application.h"
#include "Ember/Core/Layer.h"
#include "Ember/Core/Log.h"

#include "Ember/Core/Timestep.h"

#include "Ember/Core/Input.h"
#include "Ember/Core/KeyCodes.h"
#include "Ember/Core/MouseCodes.h"
#include "Ember/Renderer/OrthographicCameraController.h"

#include "Ember/ImGui/ImGuiLayer.h"

// ---ECS----------------------
#include "Ember/Scene/Scene.h"
#include "Ember/Scene/Components.h"
#include "Ember/Scene/Entity.h"
#include "Ember/Scene/ScriptableEntity.h"
// ----------------------------

// ---Renderer-----------------
#include "Ember/Renderer/Renderer.h"
#include "Ember/Renderer/Renderer2D.h"
#include "Ember/Renderer/RenderCommand.h"

#include "Ember/Renderer/Shader.h"
#include "Ember/Renderer/Buffer.h"
#include "Ember/Renderer/Framebuffer.h"
#include "Ember/Renderer/Texture.h"
#include "Ember/Renderer/SubTexture2D.h"
#include "Ember/Renderer/VertexArray.h"

#include "Ember/Renderer/OrthographicCamera.h"
// ----------------------------

// ---Physics------------------
// ----------------------------

// ---Server-------------------
#include "Ember/Server/Server.h"
#include "Ember/Server/Listener.h"
// ----------------------------
