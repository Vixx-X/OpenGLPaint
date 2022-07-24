#include "Circle.h"
#include <iostream>
#include <sstream>

void Circle::Center(int w, int h)
{
    m_coords.a.x = w/2 - 100, m_coords.a.y = h/2 - 100;
    m_coords.b.x = w/2 + 100, m_coords.b.y = h/2 + 100;
}

std::ostream& Circle::Write(std::ostream& os) const
{
    os << (m_filled ? "FILLED_CIRCLE": "CIRCLE") << " ";
    os << m_coords.a.x << " " << m_coords.a.y << " "
        << m_coords.b.x << " " << m_coords.b.y << " ";

    return Shape::Write(os);
}

std::string Circle::to_string() const
{
    std::ostringstream os;
    os << (m_filled ? "FILLED_CIRCLE": "CIRCLE") << " ";
    os << m_coords.a.x << " " << m_coords.a.y << " "
        << m_coords.b.x << " " << m_coords.b.y << " ";

    return os.str() + Shape::to_string();
}

std::istream& Circle::Read(std::istream& is)
{
    is >> m_coords.a.x >> m_coords.a.y >> m_coords.b.x >> m_coords.b.y;

    return Shape::Read(is);
}

