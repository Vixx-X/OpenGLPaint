project "freeglut"
    kind "StaticLib"
    language "C"
    architecture "x86"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"

    targetname "freeglut_static"

    includedirs { "freeglut/include", "freeglut/src", "freeglut/src/mswin" }

    files
    {
        "freeglut/src/*.c",
        "freeglut/src/*.h",
        "freeglut/src/util/*.c",
    }

    defines
    {
        "FREEGLUT_STATIC",
        "FREEGLUT_LIB_PRAGMAS=1",
        "NDEBUG",
        "GLUT_DISABLE_ATEXIT_HACK",
    }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "On"

        links { "GL" }

        files
        {
            "freeglut/src/x11/*.c",
        }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        
        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "_WIN32",
            "TARGET_HOST_MS_WINDOWS",
            "_WIN32_WINNT=0x0601",
        }

        includedirs { "freeglut/src/mswin" }

        files
        {
            "freeglut/src/mswin/*.c",
            "freeglut/src/mswin/*.h",
        }


    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
