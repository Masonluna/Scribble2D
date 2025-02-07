#pragma once
#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"
#include <Scribble2D/Renderer/TextRenderer.h>
#include <Scribble2D/Renderer/Renderer.h>

namespace Scribble {

	class Application
	{
	public:
		Application();
		Application(WindowSpecs specs);
		virtual ~Application();

		void Run();

		Window& GetWindow() { return *m_Window; }
		Renderer& GetRenderer() { return m_Renderer; }
		TextRenderer& GetTextRenderer() { return m_TextRenderer; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Renderer m_Renderer;
		TextRenderer m_TextRenderer;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;

		static Application* s_Instance;

	};

	// Should be defined by the client
	Application* CreateApplication();

}