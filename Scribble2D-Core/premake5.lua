project "Scribble2D-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "scbpch.h"
	pchsource "src/scbpch.cpp"

    files {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs {
        "src",
        "src/Scribble2D",
        "vendor/stb_image",
        "vendor/GLFW/include",
        "vendor/Glad/include",
        "vendor/glm/glm-1.0.1",
        "vendor/spdlog/include"
    }

    libdirs {
        "vendor/GLFW/lib",
        "vendor/spdlog/lib",
        "vendor/Glad/build/Debug"
    }
    links {
        "glfw3_mt.lib",
        "Glad",
        "opengl32.lib",
        "spdlog.lib"
    }

    defines { "RESOURCE_PATH=\"" .. path.getabsolute("res/") .. "/\"" }


    filter "system:windows"
        systemversion "latest"
        defines {
            "SCRIBBLE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines { "CORE_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "CORE_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "action:vs*"
        buildoptions { "/utf-8" }