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
		m_Renderer.DrawQuad(glm::vec2(100.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(140.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(180.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(220.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		m_Renderer.DrawQuad(glm::vec2(260.0f + frame++, 200.0f), glm::vec2(35.0f, 35.0f), 0.0f, glm::vec3(1.0f, 0.0f, 1.0f));

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