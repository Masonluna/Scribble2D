#include <Scribble2D.h>


class ExampleLayer : public Scribble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		SCB_INFO("ExampleLayer::Update");
	}

	void OnEvent(Scribble::Event& event) override
	{
		SCB_TRACE("{0}", event);
	}

private:
	Scribble::Renderer m_Renderer;
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