workspace "GladLibrary"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "Glad"
    kind "StaticLib"
    language "C"
    targetdir "build/%{cfg.buildcfg}" -- Output directory for the library
    objdir "build/obj/%{cfg.buildcfg}" -- Intermediate object files

    files { "src/**.c" } -- Source files
    includedirs { "include" } -- Header files directory

    filter "configurations:Debug"
        symbols "On" -- Enable debug symbols
        optimize "Off"

    filter "configurations:Release"
        optimize "On" -- Optimize for release
        symbols "Off"
