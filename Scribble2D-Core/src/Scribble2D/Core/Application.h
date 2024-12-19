#pragma once
#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

namespace Scribble {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		Window& GetWindow() { return *m_Window; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;

	};

	// Should be defined by the client
	Application* CreateApplication();

}