#include "Emberpch.h"
#include "Ember/Renderer/GraphicsContext.h"

#include "Ember/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"


namespace Ember
{

    Scope<GraphicsContext> GraphicsContext::Create(void *window)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
            case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}