#include "scbpch.h"
#include "Renderer/ResourceManager.h"
#include "Application.h"
#include "Utils/Utils.h"

#include <glad/glad.h>

namespace Scribble {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// Set up window and GLFW context.
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));


	}
	
	Application::~Application()
	{}

	void Application::Run()
	{
		 SCB_INFO("Hello, Application!");
		 while (m_Running) {
			 glClearColor(0, 0, 0, 1);
			 glClear(GL_COLOR_BUFFER_BIT);

			 float time = Time::GetTime();
			 Timestep timestep = time - m_LastFrameTime;
			 m_LastFrameTime = time;

			 if (!m_Minimized) {


				 for (Layer* layer : m_LayerStack) {
					 layer->OnUpdate(timestep);
				 }


			 }
			 m_Window->OnUpdate();
		 }
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		return false;
	}
}