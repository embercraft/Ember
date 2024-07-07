#include "Emberpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ember {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		EMBER_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		EMBER_PROFILE_FUNCTION();
		
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EMBER_CORE_ASSERT(status, "Failed to initialize Glad!");

		EMBER_CORE_INFO("OpenGL Info:");
		EMBER_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		EMBER_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		EMBER_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		EMBER_PROFILE_FUNCTION();
		
		glfwSwapBuffers(m_WindowHandle);
	}   
}