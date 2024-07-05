#pragma once

#include "Ember/Core/Core.h"
#include "Ember/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Ember {
	class EMBER_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}