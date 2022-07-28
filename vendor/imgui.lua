project "ImGui"
    kind "StaticLib"
    language "C++"
    architecture "x86"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"

    includedirs { "imgui/", "freeglut/include" }

    files
    {
        "imgui/*.cpp",
        "imgui/backends/imgui_impl_glut.cpp",
        "imgui/backends/imgui_impl_opengl2.cpp",
    }

    defines
    {
        "FREEGLUT_STATIC",
        "FREEGLUT_LIB_PRAGMAS=1",
        "NDEBUG",
        "GLUT_DISABLE_ATEXIT_HACK",
    }

    links { "freeglut" }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "On"

        links { "GL" }

        defines
        {
            "_IMGUI_X11"
        }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        includedirs { "freeglut/src/mswin" }

        defines
        {
            "_IMGUI_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
            "_WIN32",
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
