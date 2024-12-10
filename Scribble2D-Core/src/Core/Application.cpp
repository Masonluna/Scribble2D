#include "Application.h"
#include <iostream>
#include "Log.h"
namespace Scribble {
	Application::Application()
	{

	}
	
	Application::~Application()
	{}

	void Application::Run()
	{
		 SCB_INFO("Hello, Application!");
	}
}