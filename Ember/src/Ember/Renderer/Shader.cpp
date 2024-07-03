#include "Emberpch.h"

#include "Renderer.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Ember {
    
    Shader* Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
            case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    Shader* Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    EMBER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
            case RendererAPI::API::Vulkan:  EMBER_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
        }

        EMBER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
}
