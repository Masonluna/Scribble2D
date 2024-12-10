project "Scribble2D-Core"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/src/Core",
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
        "glfw3.lib",
        "opengl32.lib",
        "spdlog.lib",
        "Glad"
    }

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