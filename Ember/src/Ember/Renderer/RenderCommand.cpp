#include "Emberpch.h"
#include "Ember/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ember {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}
