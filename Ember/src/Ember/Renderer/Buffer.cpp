#include "Emberpch.h"
#include "Ember/Renderer/Buffer.h"

#include "Ember/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Buffer.h"

namespace Ember {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
			case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		}

		EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
			case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		}

		EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	EMBER_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
			case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "Renderer API::Vulkan is currently not supported!"); return nullptr;
		}

		EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;	   
	}

}