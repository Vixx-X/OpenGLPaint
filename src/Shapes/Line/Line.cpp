#include "Line.h"
#include <iostream>
#include <sstream>

void Line::Set(int x0, int y0, int x1, int y1)
{
    m_coords = Vec4(x0, y0, x1, y1);
}

Vec4 &Line::GetCoords()
{
    return m_coords;
}

std::vector<std::reference_wrapper<float>> Line::GetVertex()
{
    std::vector<std::reference_wrapper<float>> ret = {
        std::ref(m_coords.x), std::ref(m_coords.y),
        std::ref(m_coords.z), std::ref(m_coords.w)
    };
    return ret;
}

void Line::Render()
{
    int x0 = m_coords.a.x, y0 = m_coords.a.y,
        x1 = m_coords.b.x, y1 = m_coords.b.y;

    SetColorPixel();

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (true) {
        PutPixel(x0, y0);
        if (x0 == x1 and y0 == y1) break;
        int e2 = 2 * error;
        if (e2 >= dy) {
            if (x0 == x1) break;
            error += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) break;
            error += dx;
            y0 += sy;
        }
    }
}

void Line::HardwareRender()
{
    SetColorPixel();

    glBegin(GL_LINES);
    PutVertex(m_coords.a.x, m_coords.a.y);
    PutVertex(m_coords.b.x, m_coords.b.y);
    glEnd();
}

bool Line::OnClick(int x, int y)
{
    const int ERR = 3; // +- error
    Vec2 p = {(float)x, (float)y};
    float pa = p.dist(m_coords.a), pb = p.dist(m_coords.b), ab = m_coords.a.dist(m_coords.b);
    return std::abs(ab - pa - pb) < ERR;
}

void Line::OnMove(int x, int y)
{
    m_coords.a.x += x, m_coords.a.y += y;
    m_coords.b.x += x, m_coords.b.y += y;
}

void Line::Center(int w, int h)
{
    m_coords.a.x = w/2 - 100, m_coords.a.y = h/2;
    m_coords.b.x = w/2 + 100, m_coords.b.y = h/2;
}

std::ostream& Line::Write(std::ostream& os) const
{
    os << "LINE ";
    os << m_coords.a.x << " " << m_coords.a.y << " "
       << m_coords.b.x << " " << m_coords.b.y << " "
       << m_border_color.r <<  " " << m_border_color.g << " "
       << m_border_color.b;
    return os;
}

std::string Line::to_string() const
{
    std::ostringstream os;
    os << "LINE ";
    os << m_coords.a.x << " " << m_coords.a.y << " "
       << m_coords.b.x << " " << m_coords.b.y << " "
       << m_border_color.r <<  " " << m_border_color.g << " "
       << m_border_color.b;
    return os.str();
}

std::istream& Line::Read(std::istream& is)
{
    is >> m_coords.a.x >> m_coords.a.y >> m_coords.b.x >> m_coords.b.y
       >> m_border_color.x >> m_border_color.y >> m_border_color.z;
    return is;
}
