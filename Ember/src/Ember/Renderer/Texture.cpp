#include "Emberpch.h"
#include "Ember/Renderer/Texture.h"
#include "Ember/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ember {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	EMBER_CORE_ASSERT(false, "Renderer API is not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
			case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "Renderer API is not yet supported"); return nullptr;
		}
	}

}