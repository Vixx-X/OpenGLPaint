#pragma once

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include "UI/Base.h"

namespace GLPaint
{
    void RenderUI();
    void Render();
    void Start(const char * title, int argc, char** argv);
}

