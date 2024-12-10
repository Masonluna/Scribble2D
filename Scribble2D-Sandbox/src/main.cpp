#include <iostream>
#include <Scribble2D.h>


class Sandbox : public Scribble::Application
{
public:

	Sandbox() {}
	~Sandbox() {}
};

Scribble::Application* Scribble::CreateApplication()
{
	return new Sandbox();
}