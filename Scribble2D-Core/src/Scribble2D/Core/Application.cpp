#include "scbpch.h"
#include "Scribble2D/Renderer/ResourceManager.h"
#include "Scribble2D/Core/Application.h"
#include "Scribble2D/Utils/Utils.h"

#include <glad/glad.h>

namespace Scribble {


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_Renderer.Init();
		m_TextRenderer.Init();
	}

	Application::Application(WindowSpecs specs)
	{
		// Set up window and GLFW context.
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(specs));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_Renderer.Init();
		m_TextRenderer.Init();
	}
	
	Application::~Application()
	{}

	void Application::Run()
	{
		 SCB_INFO("Hello, Application!");
		 while (m_Running) {
			 m_Renderer.Clear();

			 float time = Time::GetTime();
			 Timestep timestep = time - m_LastFrameTime;
			 m_LastFrameTime = time;

			 m_Renderer.BeginScene();
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
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

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

		m_Window->OnWindowResize(e.GetWidth(), e.GetHeight());
		m_Minimized = false;
		return false;
	}
}