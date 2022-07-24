#include "Rectangle.h"
#include <iostream>
#include <sstream>

void Rectangle::Set(int x0, int y0, int x1, int y1)
{
    m_coords = Vec4(x0, y0, x1, y1);
}

void Rectangle::Render()
{
    Vec2 a = {
        std::min(m_coords.a.x, m_coords.b.x),
        std::min(m_coords.a.y, m_coords.b.y)
    };

    Vec2 b = {
        std::max(m_coords.a.x, m_coords.b.x),
        std::max(m_coords.a.y, m_coords.b.y)
    };

    SetColorPixel();
    PutHLine(a.x, a.y, b.x);
    PutHLine(a.x, b.y, b.x);

    for (int t = a.y + 1; t < b.y; ++t) {
        PutPixel(a.x, t);

        if (m_filled) {
            SetFillColorPixel();
            PutHLine(a.x+1, t, b.x-1);
            SetColorPixel();
        }

        PutPixel(b.x, t);
    }
}

void Rectangle::HardwareRender()
{
    if (m_filled) {
        SetFillColorPixel();

        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_QUADS);
        glVertex2i(m_coords.a.x, m_coords.a.y);
        glVertex2i(m_coords.b.x, m_coords.a.y);
        glVertex2i(m_coords.b.x, m_coords.b.y);
        glVertex2i(m_coords.a.x, m_coords.b.y);
        glEnd();
        glPolygonMode(GL_FRONT, GL_LINE);
    }

    SetColorPixel();

    glBegin(GL_QUADS);
    glVertex2i(m_coords.a.x, m_coords.a.y);
    glVertex2i(m_coords.b.x, m_coords.a.y);
    glVertex2i(m_coords.b.x, m_coords.b.y);
    glVertex2i(m_coords.a.x, m_coords.b.y);
    glEnd();
}

bool Rectangle::OnClick(int x, int y)
{
    // determinar la distancia del click a la línea
    // si es mejor a un umbral (e.g. 3 píxeles) entonces
    // retornas true
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
