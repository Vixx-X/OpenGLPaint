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

        Vec4 m_bg_color;
        std::vector<Shape*> m_primitives;
        bool m_hardware_acc;
        int m_idx;
        float m_psize;

        Canvas()
            : m_bg_color(1.0f, 1.0f, 1.0f, 1.0f), m_primitives(),
            m_hardware_acc(), m_idx(-1), m_psize() { }

        void ToggleHardwareAcceleration();
        void SetBg(float r, float g, float b);

        void AddPrimitive(Shape &primitive);
        void Clear();

        void Save();
        void Load();

        void Render();

        bool IsSelected();
        void Unselect();
        void Select(int x, int y);
        Shape * &GetSelected();

        void Delete();

        void Foreground();
        void Background();
        void Up();
        void Down();

        Shape * Pop();

    };
}
