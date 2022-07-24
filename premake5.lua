workspace "OpenGLPaint"
    configurations { "Debug", "Release" }
    startproject "OpenGLPaint"

    flags { "MultiProcessorCompile" }

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

    includedirs { "src", "vendor/freeglut/include", "vendor/imgui", "vendor/imgui/backends", "vendor/imgui/examples", "vendor/tinyfiledialogs" }

    files { "src/**.cpp", "src/**.h" }

    libdirs { "vendor/freeglut/lib", os.findlib("X11") }

    links {"glut", "GL", "ImGui", "X11", "Xext", "Xxf86vm", "Xrandr", "Xcursor", "Xinerama", "Xi" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

include "vendor/imgui.lua"
include "vendor/tinyfiledialogs.lua"

