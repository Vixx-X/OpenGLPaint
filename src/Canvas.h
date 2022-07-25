#pragma once

#include "Misc/Base.h"
#include "Shapes/Base.h"

#include <vector>
#include <string>

#include "tinyfiledialogs.h"

namespace GLPaint
{
    struct Canvas
    {

        int m_W, m_H, m_Wx, m_Hy;
        float m_D;
        Vec4 m_bg_color, m_gizmo_color;
        Vec3 m_border_color, m_filler_color;
        std::vector<Shape*> m_primitives;
        bool m_hardware_acc;
        int m_idx;
        float m_psize, m_gizmo_psize;

        Canvas()
            : m_W{}, m_H{}, m_Wx{}, m_Hy{}, m_D{1.0f},
            m_bg_color(1.0f, 1.0f, 1.0f, 1.0f),
            m_gizmo_color(1.0f, 0.0f, 0.0f, 1.0f),
            m_border_color(0.0f, 0.0f, 0.0f),
            m_filler_color(1.0f, 1.0f, 1.0f),
            m_primitives(), m_hardware_acc(), m_idx(-1),
            m_psize(), m_gizmo_psize(10) { }

        void ToggleHardwareAcceleration();
        void SetBg(float r, float g, float b);

        void AddPrimitive(Shape &primitive);
        void AddPrimitive(std::string primitive_name);
        void Clear();

        void Save();
        void Load();

        void Render();

        bool IsSelected();
        void Unselect();
        void Select(int x, int y);
        bool Hover(int x, int y);
        Shape * &GetSelected();

        void Delete();

        void Foreground();
        void Background();
        void Up();
        void Down();

        Shape * Pop();

    };
}
