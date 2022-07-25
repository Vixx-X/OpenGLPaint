#pragma once

#include "../../Shapes/Shape.h"
#include "../../Misc/Base.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include "imgui.h"

#include <istream>
#include <ostream>

class Gizmo
{
    private:
        int m_editing_idx;
        float* m_circle_size;
        Vec4* m_color;
        Vec2 m_prev;

    public:
        Shape *shape;
        bool IsEditing;

        Gizmo(Shape * s, Vec4* color, float* m_circle_size)
            : shape(s), IsEditing(false), m_editing_idx(-1),
            m_circle_size(m_circle_size), m_color(color), m_prev{-1, -1} {}

        ~Gizmo() = default;

        void PutCircle(float x, float y);

        bool Select(float x, float y);
        bool Hover(float x, float y);

        void Render();
};
