#include <Scribble2D/Scribble2D.h>
#include "Scribble2D/Renderer/TextRenderer.h"
#include "Scribble2D/Events/MouseEvent.h"
#include "Scribble2D/Renderer/ResourceManager.h"


class ExampleLayer : public Scribble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_Renderer.Init();
		m_TextRenderer.Init();
		m_TextRenderer.LoadFont("fonts/ocraext.TTF", 24);
	}

	void OnUpdate(Scribble::Timestep ts) override
	{
		m_TimeElapsed += ts.GetSeconds();
		while (m_TimeElapsed > 0.01f) {
			step++;
			m_TimeElapsed -= 0.01f;
		}
		//SCB_INFO("ExampleLayer::Update");
		m_Renderer.DrawQuad(glm::vec2(0.0, 200.0f), 150.0f, 150.0f, 0.0f, Scribble::ResourceManager::GetTexture("Container"));
		m_Renderer.DrawQuad(glm::vec2(40.0f, 200.0f), 35.0f, 35.0f, 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(80.0f, 200.0f), 35.0f, 35.0f, 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(120.0f, 200.0f),35.0f, 35.0f, 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(160.0f, 200.0f),35.0f, 35.0f, 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));

		m_TextRenderer.DrawString("Hello, World!", glm::vec2(5.0f, 5.0f), 1.0f, glm::vec3(1.0f, 0.0f, 1.0f));
	}

	void OnEvent(Scribble::Event& event) override
	{
		if (event.GetEventType() == Scribble::EventType::MouseButtonPressed) {
			Scribble::MouseButtonPressedEvent& temp = static_cast<Scribble::MouseButtonPressedEvent&>(event);
			if (temp.GetMouseButton() == Scribble::MouseButtonLeft) {
				SCB_TRACE("{0}", event);
			}
		}

	}

private:
	Scribble::Renderer m_Renderer;
	Scribble::TextRenderer m_TextRenderer;
	unsigned int step = 2;
	float m_TimeElapsed = 0.0f;
};

class Sandbox : public Scribble::Application
{
public:

	Sandbox(Scribble::WindowSpecs specs)
		:Scribble::Application(specs)
	{
		Scribble::ResourceManager::LoadTexture("container.jpg", false, "Container");
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Scribble::Application* Scribble::CreateApplication()
{
	Scribble::WindowSpecs specs("Sandbox", 1280, 720);
	return new Sandbox(specs);
}