#include "Canvas.h"
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>

char const * lFilterPatterns[2] = { "*.txt", "*.text" };

namespace GLPaint
{

    void Canvas::ToggleHardwareAcceleration()
    {
        m_hardware_acc = !m_hardware_acc;
    }

    void Canvas::AddPrimitive(Shape &primitive)
    {
        m_primitives.push_back(&primitive);
    }

    void Canvas::AddPrimitive(std::string primitive_name)
    {
        Shape * shape = nullptr;
        if (Shapes::GetPrimitive(primitive_name, shape)) {
            shape->Center(m_W, m_H);
            AddPrimitive(*shape);
            m_idx = m_primitives.size() - 1;
        }
    }

    void Canvas::Clear()
    {
        Unselect();
        for (auto p : m_primitives) {
            delete p;
        }
        m_primitives.clear();
    }

    void Canvas::Save()
    {
        char* filename;
        filename = tinyfd_saveFileDialog(
                "Saving progress...",
                NULL,
                2,
                lFilterPatterns,
                NULL);

        if (!filename)
            return;

        {
            std::ofstream ostrm{std::string(filename)};

            ostrm << "BACKGROUND "
                  << m_bg_color.x << " " << m_bg_color.y << " "
                  << m_bg_color.z << '\n';

            for (auto &p : m_primitives) {
                ostrm << p << '\n';
            }
        }
    }

    void Canvas::Load()
    {
        char* filename;
        filename = tinyfd_openFileDialog(
                "Load previous progress...",
                NULL,
                2,
                lFilterPatterns,
                NULL,
                false);

        if (!filename)
            return;

        {
            std::ifstream istrm{std::string(filename)};
            std::string line, token;
            int nLine = 0;
            while (getline(istrm, line)) {
                std::stringstream sstr(line);
                Shape* shape = nullptr;

                nLine++;
                sstr >> token;

                if (token == "BACKGROUND") {
                    float r, g, b;
                    sstr >> r >> g >> b;
                    SetBg(r, g, b);
                    continue;
                }

                if (Shapes::GetPrimitive(token, shape) and (sstr >> shape)) {
                    AddPrimitive(*shape);
                    continue;
                }

                sstr.clear();
                std::cout << "Error at line #" << nLine << '\n';
            }
        }
    }

    void Canvas::SetBg(float r, float g, float b)
    {
        m_bg_color = Vec4(r, g, b, 1.00f);
    }

    void Canvas::Render()
    {
        for (auto &p : m_primitives) {
            if (m_hardware_acc) {
                p->HardwareRender();
            } else {
                p->Render();
            }
        }
    }

    bool Canvas::IsSelected()
    {
        return m_idx != -1;
    }

    void Canvas::Unselect()
    {
        m_idx = -1;
    }

    void Canvas::Select(int x, int y)
    {
        for (int idx=m_primitives.size() - 1; ~idx; --idx) {
            auto p = m_primitives[idx];
            if (p->OnClick(x, y)) {
                m_idx = idx;
                return;
            }
        }
        Unselect();
    }

    bool Canvas::Hover(int x, int y)
    {
        for (int idx=m_primitives.size() - 1; ~idx; --idx) {
            auto p = m_primitives[idx];
            if (p->OnClick(x, y)) return true;
        }
        return false;
    }

    Shape * &Canvas::GetSelected()
    {
        return m_primitives[m_idx];
    }

    Shape * Canvas::Pop()
    {
        auto p = GetSelected();
        m_primitives.erase(m_primitives.begin() + m_idx);
        Unselect();
        return p;
    }

    void Canvas::Delete()
    {
        Shape *p = Pop();
        delete p;
    }

    void Canvas::Foreground()
    {
        if (m_idx == m_primitives.size() - 1) return;
        auto p = Pop();
        m_primitives.push_back(p);
        m_idx = m_primitives.size() - 1;
    }

    void Canvas::Background()
    {
        if (m_idx == 0) return;
        auto p = Pop();
        m_primitives.insert(m_primitives.begin(), p);
        m_idx = 0;
    }

    void Canvas::Up()
    {
        if (m_idx == m_primitives.size() - 1) return;
        std::swap(m_primitives[m_idx], m_primitives[m_idx + 1]);
        m_idx++;
    }

    void Canvas::Down()
    {
        if (m_idx == 0) return;
        std::swap(m_primitives[m_idx], m_primitives[m_idx - 1]);
        m_idx--;
    }

}
