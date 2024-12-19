#pragma once
#include "Application.h"

extern Scribble::Application* Scribble::CreateApplication();

#ifndef SCB_MAIN_DEFINED
#define SCB_MAIN_DEFINED

int main(int argc, char** argv)
{
	Scribble::Log::Init();
	SCB_CORE_INFO("Scribble2D Core and Client Loggers Initialized.");

	auto app = Scribble::CreateApplication();
	app->Run();
	delete app;
}

#endif