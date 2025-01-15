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
        "vendor/Scribble2D/include"
    }

    libdirs {
        "vendor/Scribble2D/lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines { "SCRIBBLE_CORE_PLATFORM_WINDOWS" }

        filter "configurations:Debug"
            links { "Scribble2D-Core_Debug.lib" }
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            links { "Scribble2D-Core_Release.lib" }
            runtime "Release"
            optimize "On"

    filter "action:vs*"
        buildoptions { "/utf-8" }