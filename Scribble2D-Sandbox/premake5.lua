project "Scribble2D-Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "../Scribble2D-Core",
		"../Scribble2D-Core/src",
		"../Scribble2D-Core/vendor",
        "../Scribble2D-Core/vendor/glm/glm-1.0.1",
        "../Scribble2D-Core/vendor/spdlog/include"
    }

    links {
        "Scribble2D-Core"
    }

    filter "system:windows"
        systemversion "latest"

        defines { "SCRIBBLE_CORE_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines "SCRIBBLE_APP_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SCRIBBLE_APP_RELEEASE"
        runtime "Release"
        optimize "on"

    filter "action:vs*"
        buildoptions { "/utf-8" }