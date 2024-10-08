#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Window.h"
#include "Ember/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Ember {

	class LinuxWindow : public Window
	{
	public:
		LinuxWindow(const WindowProps& props);
		virtual ~LinuxWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title, FilePath;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}