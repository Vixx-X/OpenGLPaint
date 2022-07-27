workspace "OpenGLPaint"
    configurations { "Debug", "Release" }
    startproject "OpenGLPaint"

    flags { "MultiProcessorCompile" }
    conformancemode "true"

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "OpenGLPaint"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { "src", "vendor/freeglut/include", "vendor/imgui", "vendor/imgui/backends", "vendor/tinyfiledialogs" }

    files { "src/**.cpp", "src/**.h" }

    links { "freeglut", "ImGui", "tinyfiledialogs" }

    defines
    {
        "FREEGLUT_STATIC"
    }

    filter "system:linux"
        links { "GL", "dl", "pthread", "X11", "Xext", "Xxf86vm", "Xrandr", "Xcursor", "Xinerama", "Xi" }
        libdirs { os.findlib("X11") }

        defines { "_X11" }

    filter "system:windows"
        links { "OpenGL32" }
        defines { "_WINDOWS" }

include "vendor/freeglut.lua"
include "vendor/imgui.lua"
include "vendor/tinyfiledialogs.lua"

