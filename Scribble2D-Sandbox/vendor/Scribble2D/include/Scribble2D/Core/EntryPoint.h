#pragma once
#include "Application.h"

extern Scribble::Application* Scribble::CreateApplication();

int main(int argc, char** argv)
{
	Scribble::Log::Init();
	SCB_CORE_INFO("Scribble2D Core and Client Loggers Initialized.");

	auto app = Scribble::CreateApplication();
	app->Run();
	delete app;
}