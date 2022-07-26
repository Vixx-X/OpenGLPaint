#include "Triangle.h"
#include "../Line/Line.h"
#include <iostream>
#include <algorithm>
#include <sstream>

namespace GLPaint::Shapes
{

    void Triangle::Set(int x0, int y0, int x1, int y1, int x2, int y2)
    {
        m_coords[0] = {(float)x0, (float)y0};
        m_coords[1] = {(float)x1, (float)y1};
        m_coords[2] = {(float)x2, (float)y2};
    }

    std::vector<std::reference_wrapper<float>> Triangle::GetVertex()
    {
        std::vector<std::reference_wrapper<float>> ret = {
            std::ref(m_coords[0].x), std::ref(m_coords[0].y),
            std::ref(m_coords[1].x), std::ref(m_coords[1].y),
            std::ref(m_coords[2].x), std::ref(m_coords[2].y)
        };
        return ret;
    }

    void Triangle::RenderInside()
    {
        std::array<Vec2,3> aux = m_coords;

        if ((aux[1].x - aux[0].x)*(aux[2].y - aux[0].y) -
                (aux[1].y - aux[0].y)*(aux[2].x - aux[0].x) > 0)
            std::swap(aux[0], aux[2]);

        float y1 = aux[0].y;
        float y2 = aux[1].y;
        float y3 = aux[2].y;

        float x1 = aux[0].x;
        float x2 = aux[1].x;
        float x3 = aux[2].x;

        // Deltas
        float Dx12 = x1 - x2;
        float Dx23 = x2 - x3;
        float Dx31 = x3 - x1;

        float Dy12 = y1 - y2;
        float Dy23 = y2 - y3;
        float Dy31 = y3 - y1;

        // Bounding rectangle
        int minx = (int)std::min({x1, x2, x3});
        int maxx = (int)std::max({x1, x2, x3});
        int miny = (int)std::min({y1, y2, y3});
        int maxy = (int)std::max({y1, y2, y3});

        // Constant part of half-edge functions
        float C1 = Dy12 * x1 - Dx12 * y1;
        float C2 = Dy23 * x2 - Dx23 * y2;
        float C3 = Dy31 * x3 - Dx31 * y3;

        float Cy1 = C1 + Dx12 * miny - Dy12 * minx;
        float Cy2 = C2 + Dx23 * miny - Dy23 * minx;
        float Cy3 = C3 + Dx31 * miny - Dy31 * minx;

        // Scan through bounding rectangle
        for(int y = miny; y < maxy; y++) {
            // Start value for horizontal scan
            float Cx1 = Cy1, Cx2 = Cy2, Cx3 = Cy3;
            for(int x = minx; x < maxx; x++)
            {
                if (Cx1 > 0 and Cx2 > 0 and Cx3 > 0)
                {
                    SetFillColorPixel();
                    PutPixel(x, y);
                    SetColorPixel();
                }
                Cx1 -= Dy12, Cx2 -= Dy23, Cx3 -= Dy31;
            }
            Cy1 += Dx12, Cy2 += Dx23, Cy3 += Dx31;
        }
    }

    void Triangle::Render()
    {
        if (m_filled)
            RenderInside();

        int M = m_coords.size();
        for (int i=0; i<M; ++i) {
            Line l(m_border_color.r, m_border_color.g, m_border_color.b);
            l.Set(m_coords[i].x, m_coords[i].y,
                    m_coords[(i + 1)%M].x, m_coords[(i + 1)%M].y);
            l.Render();
        }
    }

    void Triangle::HardwareRender()
    {
        if (m_filled) {
            SetFillColorPixel();

            glBegin(GL_TRIANGLES);
            for (auto &p : m_coords) {
                PutVertex(p.x, p.y);
            }
            glEnd();
        }

        SetColorPixel();

        int M = m_coords.size();
        glBegin(GL_LINES);
        for (int i=0; i<M; ++i) {
            PutVertex(m_coords[i].x, m_coords[i].y);
            PutVertex(m_coords[(i + 1)%M].x, m_coords[(i + 1)%M].y);
        }
        glEnd();
    }

    float Area(Vec2 p1, Vec2 p2, Vec2 p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }

    bool Triangle::OnClick(int x, int y)
    {
        if (m_filled) {
            float d1, d2, d3;
            bool has_neg, has_pos;

            d1 = Area({(float)x, (float)y}, m_coords[0], m_coords[1]);
            d2 = Area({(float)x, (float)y}, m_coords[1], m_coords[2]);
            d3 = Area({(float)x, (float)y}, m_coords[2], m_coords[0]);

            has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
            has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

            if (!(has_neg and has_pos))
                return true;
        }

        int M = m_coords.size();
        for (int i=0; i<M; ++i) {
            Line l(m_border_color.r, m_border_color.g, m_border_color.b);
            l.Set(m_coords[i].x, m_coords[i].y,
                    m_coords[(i + 1)%M].x, m_coords[(i + 1)%M].y);
            if (l.OnClick(x, y))
                return true;
        }
        return false;
    }

    void Triangle::OnMove(int x, int y)
    {
        m_coords[0].x += x, m_coords[0].y += y;
        m_coords[1].x += x, m_coords[1].y += y;
        m_coords[2].x += x, m_coords[2].y += y;
    }

    void Triangle::Center(int w, int h)
    {
        m_coords[0].x = w/2 - 100, m_coords[0].y = h/2 + 100;
        m_coords[1].x = w/2 + 100, m_coords[1].y = h/2 + 100;
        m_coords[2].x = w/2, m_coords[2].y = h/2 - 100;
    }

    std::ostream& Triangle::Write(std::ostream& os) const
    {
        os << (m_filled ? "FILLED_TRIANGLE": "TRIANGLE") << " ";
        for (auto &p : m_coords) {
            os << p.x << " " << p.y << " ";
        }
        return Shape::Write(os);
    }

    std::string Triangle::to_string() const
    {
        std::ostringstream os;
        os << (m_filled ? "FILLED_TRIANGLE": "TRIANGLE") << " ";
        for (auto &p : m_coords) {
            os << p.x << " " << p.y << " ";
        }
        return os.str() + Shape::to_string();
    }

    std::istream& Triangle::Read(std::istream& is)
    {
        for (auto &p : m_coords) {
            is >> p.x >> p.y;
        }
        return Shape::Read(is);
    }

}
