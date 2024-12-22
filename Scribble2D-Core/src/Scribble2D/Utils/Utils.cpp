#include "scbpch.h"
#include "Scribble2D/Utils/Utils.h"
#include <GLFW/glfw3.h>

namespace Scribble {
	float Time::GetTime()
	{
		return glfwGetTime();
	}
}