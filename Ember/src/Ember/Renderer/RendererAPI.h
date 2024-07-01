#pragma once

#include "Ember/Core.h"
#include "VertexArray.h"

#include <glm/glm.hpp>
#include <memory>

namespace Ember {
    
    class EMBER_API RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1, Vulkan = 2
        };

    public:
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static API getAPI() { return s_API; }

    private:
        static API s_API;
    };

}