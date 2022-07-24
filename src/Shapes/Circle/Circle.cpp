#include "Circle.h"
#include <iostream>
#include <sstream>

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
