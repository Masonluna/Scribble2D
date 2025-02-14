#include "scbpch.h"
#include <glad/glad.h>
#include "Scribble2D/Platform/Windows/WindowsWindow.h"

#include "Scribble2D/Events/ApplicationEvent.h"
#include "Scribble2D/Events/MouseEvent.h"
#include "Scribble2D/Events/KeyEvent.h"
#include "Scribble2D/Renderer/ResourceManager.h"

namespace Scribble {

	static bool s_GLFWInitialized = false;
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* userParam);
	static void GLFWErrorCallback(int error, const char* description)
	{
		SCB_CORE_ERROR("GLFW Error {0}, {1}", error, description);
	};

	Window* Window::Create(const WindowSpecs& specs)
	{
		return new WindowsWindow(specs);
	}

	WindowsWindow::WindowsWindow(const WindowSpecs& specs)
	{
		Init(specs);
		if (!glfwGetCurrentContext()) {
			SCB_CORE_FATAL("NO CURRENT CONTEXT");
		}
		ResourceManager::InitializeShaders();
	}

	WindowsWindow::~WindowsWindow()
	{}

	void WindowsWindow::Init(const WindowSpecs& specs) 
	{
		m_Data.Title = specs.Title;
		m_Data.Width = specs.Width;
		m_Data.Height = specs.Height;

		SCB_CORE_INFO("Creating Window {0} ({1}, {2})", specs.Title, specs.Width, specs.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			SCB_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		{
		#ifdef CORE_DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif
			m_Window = glfwCreateWindow((int)specs.Width, (int)specs.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}

		m_Context = std::make_unique<RenderContext>(m_Window);
		m_Context->Init();
#ifdef CORE_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, 0);
#endif

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowResizeEvent event(width, height);
				data.Width = width;
				data.Height = height;
				glViewport(0, 0, width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {

				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});


		glViewport(0, 0, m_Data.Width, m_Data.Height);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);

		// For now, Scribble will only support one window for an application.
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	bool WindowsWindow::OnWindowResize(unsigned int width, unsigned int height)
	{
		glViewport(0, 0, width, height);
		return false;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* userParam)
	{
		if (severity == GL_DEBUG_SEVERITY_HIGH) {
			SCB_CORE_FATAL("OpenGL Debug Message:");
			SCB_CORE_FATAL("Source: {0}", source);
			SCB_CORE_FATAL("Type: {0}", type);
			SCB_CORE_FATAL("ID: {0}", id);
			SCB_CORE_FATAL("Severity: GL_DEBUG_SEVERITY_HIGH");
			SCB_CORE_FATAL("Message: {0}", message);
		}
		else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
			SCB_CORE_ERROR("OpenGL Debug Message:");
			SCB_CORE_ERROR("Source: {0}", source);
			SCB_CORE_ERROR("Type: {0}", type);
			SCB_CORE_ERROR("ID: {0}", id);
			SCB_CORE_ERROR("Severity: GL_DEBUG_SEVERITY_MEDIUM");
			SCB_CORE_ERROR("Message: {0}", message);
		}
		else if (severity == GL_DEBUG_SEVERITY_LOW) {
			SCB_CORE_WARN("OpenGL Debug Message:");
			SCB_CORE_WARN("Source: {0}", source);
			SCB_CORE_WARN("Type: {0}", type);
			SCB_CORE_WARN("ID: {0}", id);
			SCB_CORE_WARN("Severity: GL_DEBUG_SEVERITY_LOW");
			SCB_CORE_WARN("Message: {0}", message);
		} 
		else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
			SCB_CORE_INFO("OpenGL Debug Message:");
			SCB_CORE_INFO("Source: {0}", source);
			SCB_CORE_INFO("Type: {0}", type);
			SCB_CORE_INFO("ID: {0}", id);
			SCB_CORE_INFO("Severity: GL_DEBUG_SEVERITY_NOTIFICATION");
			SCB_CORE_INFO("Message: {0}", message);
		}


	}
}