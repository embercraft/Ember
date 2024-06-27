#include "Emberpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ember {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}
