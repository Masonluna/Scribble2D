workspace "Scribble2D"
    architecture "x64"
    startproject "Scribble2D-Sandbox"
    staticruntime "On"
    
    configurations {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Scribble2D-Core/vendor/GLFW/include"
    IncludeDir["Glad"] = "Scribble2D-Core/vendor/Glad/include"
    IncludeDir["glm"]  = "Scribble2D-Core/vendor/glm/glm-1.0.1"
    IncludeDir["spdlog"] = "Scribble2D-Core/vendor/spdlog/include"

    include "Scribble2D-Core"
    include "Scribble2D-Sandbox"