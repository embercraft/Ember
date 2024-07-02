#pragma once

#include "Ember/Core.h"
#include "RendererAPI.h"

namespace Ember {

    class EMBER_API RenderCommand
    {
    public:
        inline static void Init()
        {
            s_RendererAPI->init();
        }

        inline static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->setClearColor(color);
        }

        inline static void Clear()
        {
            s_RendererAPI->clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_RendererAPI->drawIndexed(vertexArray);
        }

    private:
        static RendererAPI* s_RendererAPI;
    };

}