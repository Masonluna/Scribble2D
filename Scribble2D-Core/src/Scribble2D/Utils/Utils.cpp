#include "scbpch.h"
#include "Utils.h"
#include <GLFW/glfw3.h>

namespace Scribble {
	float Time::GetTime()
	{
		return glfwGetTime();
	}
}