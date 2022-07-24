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
    glVertex2i(m_coords.a.x, m_coords.a.y);
    glVertex2i(m_coords.b.x, m_coords.b.y);
    glEnd();
}

bool Line::OnClick(int x, int y)
{
    // determinar la distancia del click a la l�nea
    // si es mejor a un umbral (e.g. 3 p�xeles) entonces
    // retornas true
    return false;
}

void Line::OnMove(int x, int y)
{

}

float Line::Apply(float x)
{
    if (m_coords.x == m_coords.z) return INFINITY;
    float m = (m_coords.y - m_coords.w) / (m_coords.x - m_coords.z);
    float b = m_coords.y - m * m_coords.x;
    return m * x + b;
}

float Line::Intersec(const Line &other)
{
    // this being vertical line is not supported
    if (m_coords.x == m_coords.z) return INFINITY;

    if (other.m_coords.x == other.m_coords.z) {
        // other is vertical line
        float aux = Apply(other.m_coords.x);
        float y1 = std::max(m_coords.y, m_coords.w),
              y2 = std::min(m_coords.y, m_coords.w);
        return aux <= y2 and aux >= y1 ? other.m_coords.x : INFINITY;
    }

    float ma = (m_coords.y - m_coords.w)/(m_coords.x - m_coords.z);
    float mb = (other.m_coords.y - other.m_coords.w)/(other.m_coords.x - other.m_coords.z);

    Vec2 a = {ma, m_coords.y - ma*m_coords.x},
         b = {mb, other.m_coords.y - mb*m_coords.x};

    return a.x == b.x? INFINITY : (b.y - a.y)/(a.x - b.x);
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
