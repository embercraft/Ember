#include "Emberpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Ember/Platform/OpenGL/OpenGLBuffer.h"

namespace Ember {
    
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
            case RendererAPI::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    EMBER_CORE_ASSERT(false, "Renderer API::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indices, size);
            case RendererAPI::Vulkan:  EMBER_CORE_ASSERT(false, "Renderer API::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;       
    }

}