project "freeglut"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"

    includedirs { "freeglut/include", "freeglut/src" }

    files
    {
        "freeglut/src/*.c",
        "freeglut/src/util/*.c",
    }

    links { "GL" }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "On"

        files
        {
            "freeglut/src/x11/*.c",
        }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        defines
        {
            "_IMGUI_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files
        {
            "freeglut/src/mswin/*.c",
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
