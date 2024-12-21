#include "scbpch.h"
#include "Scribble2D/Platform/Windows/WindowsInput.h"
#include "Scribble2D/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Scribble {

	bool WindowsInput::IsKeyPressedImp(const int key)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonPressedImp(const int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		return glfwGetKey(window, button) == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImp()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float WindowsInput::GetMouseXImp()
	{
		return GetMousePositionImp().first;
	}

	float WindowsInput::GetMouseYImp()
	{
		return Input::GetMousePosition().second;
	}
}

