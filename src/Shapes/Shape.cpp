#include "Shape.h"
#include <iostream>
#include <sstream>

void Shape::PutPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Shape::PutHLine(int x1, int y, int x2)
{
    /* int a = std::min(x1, x2), b = std::max(x1, x2); */
    int a = x1, b = x2;

    glBegin(GL_POINTS);
    for (int t=a; t <= b; ++t) {
        glVertex2i(t, y);
    }
    glEnd();
}

void Shape::SetColor(float r, float g, float b)
{
    m_border_color = Vec3(r, g, b);
}

void Shape::SetFillColor(float r, float g, float b)
{
    m_filler_color = Vec4(r, g, b, 0);
}

void Shape::SetColorPixel()
{
    glColor3f(m_border_color.r, m_border_color.g, m_border_color.b);
}

void Shape::SetFillColorPixel()
{
    glColor4f(m_filler_color.x, m_filler_color.y,
            m_filler_color.z, m_filled? 1.00f : 0.00f);
}

void Shape::ToogleFill()
{
    m_filled = !m_filled;
}


void Shape::SetFill(bool filled)
{
    m_filled = filled;
}

std::string Shape::to_string() const
{
    std::ostringstream os;
    os << m_border_color.r <<  " " << m_border_color.g << " "
       << m_border_color.b;
    if (m_filled)
        os << " " << m_filler_color.x <<  " " << m_filler_color.y
           << " " << m_filler_color.z;
    return os.str();
}

std::ostream& Shape::Write(std::ostream& os) const
{
    os << m_border_color.r <<  " " << m_border_color.g << " "
       << m_border_color.b;
    if (m_filled)
        os << " " << m_filler_color.x <<  " " << m_filler_color.y
           << " " << m_filler_color.z;
    return os;
}

std::istream& Shape::Read(std::istream& is)
{
    is >> m_border_color.x >> m_border_color.y >> m_border_color.z;
    if (m_filled)
        is >> m_filler_color.x >> m_filler_color.y >> m_filler_color.z;
    return is;
}

std::ostream& operator <<(std::ostream& os, Shape*& shape)
{
    return shape->Write(os);
}

std::istream& operator >>(std::istream& is, Shape*& shape)
{
    return shape->Read(is);
}

Shape::operator std::string() const
{
    return this->to_string();
};

