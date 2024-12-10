#pragma once

namespace Scribble {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		
	};

	// Should be defined by the client
	Application* CreateApplication();

}