#include "Bezier.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

void Bezier::Set(std::vector<Vec2> new_coords)
{
    m_coords = new_coords;
}

std::vector<std::reference_wrapper<float>> Bezier::GetVertex()
{
    std::vector<std::reference_wrapper<float>> ret;
    for (int i = 0; i < m_coords.size(); ++i) {
        ret.push_back(std::ref(m_coords[i].x));
        ret.push_back(std::ref(m_coords[i].y));
    }
    return ret;
}

void Bezier::SetSize(size_t N)
{
    m_coords.resize(N, m_coords[m_size-1]);
    m_coords[N - 1].x += rand() % 100 - 50;
    m_coords[N - 1].y += rand() % 100 - 50;
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
    m_lines.clear();
    for (int t=0; t<=m_sample; ++t) {
        points.push_back(DeCasteljau(t*1.0f/m_sample, m_coords));
    }

    for (int i=1; i<points.size(); ++i) {
        Line l(m_border_color.r, m_border_color.g, m_border_color.g);
        l.Set(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
        l.Render();
        float x = std::min(points[i-1].x, points[i].x);
        m_lines.insert({x, l});
    }
}

void Bezier::HardwareRender()
{
    SetColorPixel();

    /* glEnable(GL_MULTISAMPLE); */
    glBegin(GL_LINE_STRIP);
    for (int t=0; t<=m_sample; ++t) {
        auto point = DeCasteljau(t*1.0f/m_sample, m_coords);
        PutPixel(point.x, point.y);
    }
    glEnd();
}

bool Bezier::OnClick(int x, int y)
{
    auto low = m_lines.lower_bound(x-3), upper = m_lines.lower_bound(x + 3);
    std::map<float, Line>::iterator it;
    for (it = low; it != upper; ++it) {
        if (it->second.OnClick(x, y))
            return true;
    }
    return false;
}

void Bezier::OnMove(int x, int y)
{
    for (auto &p : m_coords) {
        p.x += x;
        p.y += y;
    }
}

void Bezier::Center(int w, int h)
{
    float LineSize = 300.0f;
    float Dx = LineSize / m_coords.size();
    float x = w/2 - LineSize/2;
    bool flipY = false;
    int it = 0;
    for (auto &p : m_coords) {
        p.x = x  + it*Dx;
        p.y = h/2;
        p.y += flipY ? -100: 100;
        flipY != flipY;
        ++it;
    }
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
