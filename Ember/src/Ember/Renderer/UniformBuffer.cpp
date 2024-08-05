#include "Emberpch.h"
#include "Ember/Renderer/UniformBuffer.h"

#include "Ember/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Ember {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
            case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		}

		EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
