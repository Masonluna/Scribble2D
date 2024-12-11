#include "scbpch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Scribble {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		Log::s_CoreLogger = spdlog::stdout_color_mt("[Scribble2D]");
		Log::s_CoreLogger->set_level(spdlog::level::trace);

		Log::s_ClientLogger = spdlog::stdout_color_mt("[App]");
		Log::s_ClientLogger->set_level(spdlog::level::trace);
	}

}
