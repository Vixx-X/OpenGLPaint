#include "Ellipse.h"
#include <iostream>
#include <sstream>

void Ellipse::Set(int x0, int y0, int x1, int y1)
{
    m_coords = Vec4(x0, y0, x1, y1);
}

void Ellipse::Render()
{
    float xc = (m_coords.a.x + m_coords.b.x)/2;
    float yc = (m_coords.a.y + m_coords.b.y)/2;
    float rx = std::abs(m_coords.a.x - m_coords.b.x)/2;
    float ry = std::abs(m_coords.a.y - m_coords.b.y)/2;

    float dx, dy, d1, d2, x = 0, y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    SetColorPixel();

    // For region 1
    while (dx < dy) {

        // Print points based on 4-way symmetry
        if (m_filled) {
            SetFillColorPixel();
            PutHLine(-x + xc,  y + yc, x + xc);
            PutHLine(-x + xc, -y + yc, x + xc);
            SetColorPixel();
        }
        PutPixel(x + xc,   y + yc);
        PutPixel(-x + xc,  y + yc);
        PutPixel(x + xc,  -y + yc);
        PutPixel(-x + xc, -y + yc);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        } else {
            x++, y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
        ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0) {
        // Print points based on 4-way symmetry
        if (m_filled) {
            SetFillColorPixel();
            PutHLine(-x + xc,  y + yc, x + xc);
            PutHLine(-x + xc, -y + yc, x + xc);
            SetColorPixel();
        }
        PutPixel(x + xc,   y + yc);
        PutPixel(-x + xc,  y + yc);
        PutPixel(x + xc,  -y + yc);
        PutPixel(-x + xc, -y + yc);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        } else {
            y--, x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void Ellipse::HardwareRender()
{
    Render();
}

bool Ellipse::OnClick(int x, int y)
{
    // determinar la distancia del click a la línea
    // si es mejor a un umbral (e.g. 3 píxeles) entonces
    // retornas true
    return false;
}

void Ellipse::OnMove(int x, int y)
{

}

std::ostream& Ellipse::Write(std::ostream& os) const
{
    os << (m_filled ? "FILLED_ELLIPSE": "ELLIPSE") << " ";
    os << m_coords.a.x << " " << m_coords.a.y << " "
        << m_coords.b.x << " " << m_coords.b.y << " ";

    return Shape::Write(os);
}

std::string Ellipse::to_string() const
{
    std::ostringstream os;
    os << (m_filled ? "FILLED_ELLIPSE": "ELLIPSE") << " ";
    os << m_coords.a.x << " " << m_coords.a.y << " "
        << m_coords.b.x << " " << m_coords.b.y << " ";

    return os.str() + Shape::to_string();
}

std::istream& Ellipse::Read(std::istream& is)
{
    is >> m_coords.a.x >> m_coords.a.y >> m_coords.b.x >> m_coords.b.y;

    return Shape::Read(is);
}
