#pragma once

#include "Ember/Core.h"

#include <string>

namespace Ember {
    class EMBER_API Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_RendererID;
    };
}