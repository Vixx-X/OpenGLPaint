project "ImGui"
    kind "StaticLib"
    language "C++"
    architecture "x86_64"

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

        links { "OpenGL32" }

        defines
        {
            "_IMGUI_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
