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

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { "src", "vendor/freeglut/include", "vendor/imgui", "vendor/imgui/backends", "vendor/tinyfiledialogs" }

    files { "src/**.cpp", "src/**.h" }

    links { "freeglut", "ImGui", "tinyfiledialogs" }

    defines
    {
        "FREEGLUT_STATIC",
        "FREEGLUT_LIB_PRAGMAS=1",
        "NDEBUG",
        "GLUT_DISABLE_ATEXIT_HACK",
    }

    filter "system:linux"
        architecture "x86_64"
        links { "GL", "dl", "pthread", "X11", "Xext", "Xxf86vm", "Xrandr", "Xcursor", "Xinerama", "Xi" }
        libdirs { os.findlib("X11") }

        defines { "_X11" }

    filter "system:windows"
        architecture "x86"
        defines {
            "_WINDOWS",
            "_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
        }
        includedirs { "freeglut/src/mswin" }

        files
        {
            "freeglut/src/mswin/*.c",
            "freeglut/src/mswin/*.h",
        }

include "vendor/freeglut.lua"
include "vendor/imgui.lua"
include "vendor/tinyfiledialogs.lua"

