#include <Scribble2D.h>


class ExampleLayer : public Scribble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_Renderer.Init();
	}

	void OnUpdate() override
	{
		//SCB_INFO("ExampleLayer::Update");
		m_Renderer.DrawQuad(glm::vec2(200.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec4(1.0f, 0.0f, 1.0f, 0.1f));
		m_Renderer.DrawQuad(glm::vec2(240.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec4(1.0f, 0.0f, 1.0f, 0.1f));
		m_Renderer.DrawQuad(glm::vec2(280.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec4(1.0f, 0.0f, 1.0f, 0.1f));
		m_Renderer.DrawQuad(glm::vec2(320.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec4(1.0f, 0.0f, 1.0f, 0.1f));
		m_Renderer.DrawQuad(glm::vec2(360.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec4(1.0f, 0.0f, 1.0f, 0.1f));

	}

	void OnEvent(Scribble::Event& event) override
	{
		//SCB_TRACE("{0}", event);
	}

private:
	Scribble::Renderer m_Renderer;
	unsigned int frame = 0;
};

class Sandbox : public Scribble::Application
{
public:

	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Scribble::Application* Scribble::CreateApplication()
{
	return new Sandbox();
}