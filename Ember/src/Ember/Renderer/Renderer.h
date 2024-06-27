#pragma once

#include "Ember/Core.h"
#include "RenderCommand.h"

namespace Ember {

    class EMBER_API Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
    };

}