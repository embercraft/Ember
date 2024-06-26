#include "Emberpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ember {
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:  return new OpenGLVertexArray();
            case RendererAPI::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}