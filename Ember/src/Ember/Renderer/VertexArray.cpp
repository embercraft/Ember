#include "Emberpch.h"

#include "Ember/Renderer/VertexArray.h"
#include "Ember/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ember {
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
            case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}