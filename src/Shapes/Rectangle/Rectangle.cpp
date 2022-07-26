#include "Rectangle.h"
#include "../Line/Line.h"
#include <iostream>
#include <sstream>
#include <queue>

namespace GLPaint::Shapes
{

    void Rectangle::Set(int x0, int y0, int x1, int y1)
    {
        m_coords = Vec4(x0, y0, x1, y1);
    }

    std::vector<std::reference_wrapper<float>> Rectangle::GetVertex()
    {
        std::vector<std::reference_wrapper<float>> ret = {
            std::ref(m_coords.x), std::ref(m_coords.y),
            std::ref(m_coords.z), std::ref(m_coords.w)
        };
        return ret;
    }

    void Rectangle::Render()
    {
        std::queue<Vec2> q;
        Vec2 a = {
            std::min(m_coords.a.x, m_coords.b.x),
            std::min(m_coords.a.y, m_coords.b.y)
        };

        Vec2 b = {
            std::max(m_coords.a.x, m_coords.b.x),
            std::max(m_coords.a.y, m_coords.b.y)
        };

        for (int t = a.y + 1; t < b.y; ++t) {
            q.push({a.x, (float)t});

            if (m_filled) {
                SetFillColorPixel();
                PutHLine(a.x+1, t, b.x-1);
                SetColorPixel();
            }

            q.push({b.x, (float)t});
        }

        SetColorPixel();
        PutHLine(a.x, a.y, b.x);
        PutHLine(a.x, b.y, b.x);
        while (!q.empty()) {
            auto p = q.front();
            PutPixel(p.x, p.y);
            q.pop();
        }
    }

    void Rectangle::HardwareRender()
    {
        if (m_filled) {
            SetFillColorPixel();

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_QUADS);
            PutVertex(m_coords.a.x, m_coords.a.y);
            PutVertex(m_coords.b.x, m_coords.a.y);
            PutVertex(m_coords.b.x, m_coords.b.y);
            PutVertex(m_coords.a.x, m_coords.b.y);
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        SetColorPixel();

        glBegin(GL_QUADS);
        PutVertex(m_coords.a.x, m_coords.a.y);
        PutVertex(m_coords.b.x, m_coords.a.y);
        PutVertex(m_coords.b.x, m_coords.b.y);
        PutVertex(m_coords.a.x, m_coords.b.y);
        glEnd();
    }

    bool Rectangle::OnClick(int x, int y)
    {
        if (m_filled) {
            Vec2 a = {
                std::min(m_coords.a.x, m_coords.b.x),
                std::min(m_coords.a.y, m_coords.b.y)
            };

            Vec2 b = {
                std::max(m_coords.a.x, m_coords.b.x),
                std::max(m_coords.a.y, m_coords.b.y)
            };
            return a.x <= x and b.x >= x and a.y <= y and b.y >= y;
        }

        std::array<Line, 4> lines;
        lines[0].Set(m_coords.a.x, m_coords.a.y, m_coords.a.x, m_coords.b.y);
        lines[1].Set(m_coords.a.x, m_coords.b.y, m_coords.b.x, m_coords.b.y);
        lines[2].Set(m_coords.b.x, m_coords.b.y, m_coords.b.x, m_coords.a.y);
        lines[3].Set(m_coords.a.x, m_coords.a.y, m_coords.b.x, m_coords.a.y);

        for (auto &l : lines) {
            if (l.OnClick(x, y))
                return true;
        }
        return false;
    }

    void Rectangle::OnMove(int x, int y)
    {
        m_coords.a.x += x, m_coords.a.y += y;
        m_coords.b.x += x, m_coords.b.y += y;
    }

    void Rectangle::Center(int w, int h)
    {
        m_coords.a.x = w/2 - 100, m_coords.a.y = h/2 - 100;
        m_coords.b.x = w/2 + 100, m_coords.b.y = h/2 + 100;
    }

    std::ostream& Rectangle::Write(std::ostream& os) const
    {
        os << (m_filled ? "FILLED_RECTANGLE": "RECTANGLE") << " ";
        os << m_coords.a.x << " " << m_coords.a.y << " "
            << m_coords.b.x << " " << m_coords.b.y << " ";

        return Shape::Write(os);
    }

    std::string Rectangle::to_string() const
    {
        std::ostringstream os;
        os << (m_filled ? "FILLED_RECTANGLE": "RECTANGLE") << " ";
        os << m_coords.a.x << " " << m_coords.a.y << " "
            << m_coords.b.x << " " << m_coords.b.y << " ";

        return os.str() + Shape::to_string();
    }

    std::istream& Rectangle::Read(std::istream& is)
    {
        is >> m_coords.a.x >> m_coords.a.y >> m_coords.b.x >> m_coords.b.y;

        return Shape::Read(is);
    }

}
