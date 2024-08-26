#include "Emberpch.h"
#include "Platform/Linux/LinuxWindow.h"

#include "Ember/Core/Input.h"

#include "Ember/Renderer/Renderer.h"

#include "Ember/Events/ApplicationEvent.h"
#include "Ember/Events/MouseEvent.h"
#include "Ember/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <stb_image/stb_image.h>

namespace Ember {

	static uint32_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		if (!(error == 65548 && std::getenv("WAYLAND_DISPLAY")))
		{
			EMBER_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
		}
	}

	LinuxWindow::LinuxWindow(const WindowProps& props)
	{
		EMBER_PROFILE_FUNCTION();
		
		Init(props);
	}

	LinuxWindow::~LinuxWindow()
	{
		EMBER_PROFILE_FUNCTION();
		
		Shutdown();
	}

	void LinuxWindow::Init(const WindowProps& props)
	{
		EMBER_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.FilePath = props.filePath;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EMBER_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (std::getenv("WAYLAND_DISPLAY"))
		{
			EMBER_CORE_INFO("Running on Wayland display server");
		}
		else if (std::getenv("DISPLAY"))
		{
			EMBER_CORE_INFO("Running on X11 display server");
		}
		else
		{
			EMBER_CORE_WARN("No display server detected");
		}		
		
		if (s_GLFWWindowCount == 0)
		{
			EMBER_PROFILE_SCOPE("glfwInit");

			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EMBER_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			EMBER_PROFILE_SCOPE("glfwCreateWindow");

			#if defined(EMBER_DEBUG)
				if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
					glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif

			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		{
			EMBER_PROFILE_SCOPE("glfwSetWindowIcon");
			// Set the window icon
			GLFWimage icons[1];

			if(m_Data.FilePath != "Default")
			{
				icons[0].pixels = stbi_load(m_Data.FilePath.c_str() , &icons[0].width, &icons[0].height, 0, 4);
				EMBER_ASSERT(icons[0].pixels, "Failed to load icon!!");
				glfwSetWindowIcon(m_Window, 1, icons);
				stbi_image_free(icons[0].pixels);	
			}
		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = (uint32_t)width;
			data.Height = (uint32_t)height;

			WindowResizeEvent event((uint32_t)width, (uint32_t)height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;	
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;	
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (iconified)	// Minimized
			{
				WindowMinimizedEvent event;
				data.EventCallback(event);
			}
			else			// Restored
			{
				WindowRestoredEvent event;
				data.EventCallback(event);
			}
		});
		
	}

	void LinuxWindow::Shutdown()
	{
		EMBER_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			EMBER_PROFILE_SCOPE("glfwTerminate");

			glfwTerminate();
		}
	}

	void LinuxWindow::OnUpdate()
	{
		EMBER_PROFILE_FUNCTION();
		
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void LinuxWindow::SetVSync(bool enabled)
	{
		EMBER_PROFILE_FUNCTION();
		
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}