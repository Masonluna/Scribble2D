#include "scbpch.h"
#include "glad/glad.h"
#include "RenderContext.h"

Scribble::RenderContext::RenderContext(GLFWwindow* window)
	:m_Window(window)
{
	SCB_CORE_ASSERT(window, "Window is null");
}

void Scribble::RenderContext::Init()
{
	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	SCB_CORE_ASSERT(status, "Failed to initialize Glad");

	SCB_CORE_INFO("OpenGL Info");


	SCB_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	SCB_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	SCB_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void Scribble::RenderContext::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}
