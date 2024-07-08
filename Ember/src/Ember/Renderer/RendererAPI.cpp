#include "Emberpch.h"
#include "Ember/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ember {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> Ember::RendererAPI::Create()
	{
		switch(s_API)
		{
			case RendererAPI::API::None:	EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
			case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		}

		EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}