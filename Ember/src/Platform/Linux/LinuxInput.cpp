#include "Emberpch.h"
#include "Platform/Linux/LinuxInput.h"

#include "Ember/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Ember
{
	bool LinuxInput::IsKeyPressedImpl(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	};

	bool LinuxInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

		return state == GLFW_PRESS;
	}

	std::pair<float, float> LinuxInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float LinuxInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	};

	float LinuxInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	};	
}