#pragma once

extern Scribble::Application* Scribble::CreateApplication();

int main(int argc, char** argv)
{
	Scribble::Log::Init();
	SCB_CORE_INFO("Hello, Scribble2D!");
	SCB_INFO("Hello, Client!");
}