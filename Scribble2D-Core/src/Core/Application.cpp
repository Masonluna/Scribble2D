#include "Application.h"
#include <iostream>
#include "Log.h"

#include <glad/glad.h>

namespace Scribble {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}
	
	Application::~Application()
	{}

	void Application::Run()
	{
		 SCB_INFO("Hello, Application!");

		 while (m_Running) {
			 // GL stuff
			 glClearColor(1, 0, 1, 1);
			 glClear(GL_COLOR_BUFFER_BIT);

			 for (Layer* layer : m_LayerStack) {
				 layer->OnUpdate();
			 }
		 
			 m_Window->OnUpdate();
		 }
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));


		SCB_CORE_TRACE("{0}", e);


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
}