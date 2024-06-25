#pragma once

#include "Ember/Core.h"

namespace Ember {

    enum class EMBER_API RendererAPI {
        None = 0, 
        OpenGL = 1,
        Vulkan = 2
    };

    class EMBER_API Renderer
    {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }
        
    private:
        static RendererAPI s_RendererAPI;
    };

}