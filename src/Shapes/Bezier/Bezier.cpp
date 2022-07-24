#include "Bezier.h"
#include <iostream>
#include <sstream>
#include "../Line/Line.h"

void Bezier::Set(std::vector<Vec2> new_coords)
{
    m_coords = new_coords;
}

void Bezier::SetSize(size_t N)
{
    m_coords.resize(N, m_coords[m_size-1]);
    m_size = N;
}

Vec2 DeCasteljau(float t, std::vector<Vec2> coefs)
{
    size_t N = coefs.size();
    for (size_t j = 1; j < N; ++j)
        for (size_t k = 0; k < (N - j); ++k)
            coefs[k] = coefs[k] * (1 - t) + coefs[k + 1] * t;
    return coefs[0];
}

void Bezier::Render()
{
    std::vector<Vec2> points;
    for (int t=0; t<=m_sample; ++t) {
        points.push_back(DeCasteljau(t*1.0f/m_sample, m_coords));
    }

    for (int i=1; i<points.size(); ++i) {
        Line l(m_border_color.r, m_border_color.g, m_border_color.g);
        l.Set(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
        l.Render();
    }
}

void Bezier::HardwareRender()
{
    SetColorPixel();

    /* glEnable(GL_MULTISAMPLE); */
    glBegin(GL_LINE_STRIP);
    for (int t=0; t<=m_sample; ++t) {
        auto point = DeCasteljau(t*1.0f/m_sample, m_coords);
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

bool Bezier::OnClick(int x, int y)
{
    // determinar la distancia del click a la l�nea
    // si es mejor a un umbral (e.g. 3 p�xeles) entonces
    // retornas true
    return false;
}

void Bezier::OnMove(int x, int y)
{

}

std::ostream& Bezier::Write(std::ostream& os) const
{
    os << "BEZIER" << m_size;
    for (auto &p : m_coords) {
        os << " " << p.x << " " << p.y;
    }
    os << " " << m_border_color.r <<  " " << m_border_color.g << " "
        << m_border_color.b;
    return os;
}

std::string Bezier::to_string() const
{
    std::ostringstream os;

    os << "BEZIER" << m_size;
    for (auto &p : m_coords) {
        os << " " << p.x << " " << p.y;
    }
    os << " " << m_border_color.r <<  " " << m_border_color.g << " "
        << m_border_color.b;

    return os.str();
}

std::istream& Bezier::Read(std::istream& is)
{
    for (auto &p : m_coords) {
        is >> p.x >> p.y;
    }
    is >> m_border_color.r >> m_border_color.g >> m_border_color.b;
    return is;
}
