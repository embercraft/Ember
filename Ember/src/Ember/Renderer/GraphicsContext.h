#pragma once

#include "Ember/Core.h"

namespace Ember {
    class EMBER_API GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}