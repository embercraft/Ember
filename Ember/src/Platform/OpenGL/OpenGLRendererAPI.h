#pragma once

#include "Ember/Core.h"
#include "Ember/Renderer/RendererAPI.h"

namespace Ember {

    class EMBER_API OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void setClearColor(const glm::vec4& color) override;
        virtual void clear() override;

        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
        
    };

}
