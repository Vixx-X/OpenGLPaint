#pragma once

#include "../Misc/Base.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include <istream>
#include <ostream>
#include <vector>
#include <functional>

class Shape
{
    protected:
        Vec3 m_border_color;
        Vec4 m_filler_color;
        bool m_filled;
        int m_id;

    public:
        Shape() : m_border_color(0, 0, 0), m_filler_color(0, 0, 0, 0.0f),
            m_filled(false), m_id() { }
        Shape(float r, float g, float b)
            : m_border_color(r, g, b), m_filler_color(r, g, b, 0.0f),
            m_filled(false), m_id() { }

        ~Shape() = default;

        void SetID(int id);
        void PutVertex(float x, float y);
        virtual std::vector<std::reference_wrapper<float>> GetVertex() = 0;

        void PutPixel(int x, int y);
        void PutHLine(int x1, int y, int x2);

        void SetColorPixel();
        void SetFillColorPixel();

        void SetColor(float r, float g, float b);
        void SetFillColor(float r, float g, float b);

        void SetFill(bool filled = false);
        void ToogleFill();

        virtual void Render() = 0;
        virtual void HardwareRender() = 0;

        virtual bool OnClick(int x, int y) = 0;
        virtual void OnMove(int x, int y) = 0;
        virtual void Center(int w, int h) = 0;

        virtual std::ostream& Write(std::ostream& os) const = 0;
        virtual std::istream& Read(std::istream& is) = 0;

        virtual void ui(bool allowFiller = true);

        virtual std::string to_string() const;
        operator std::string() const;
};

std::ostream& operator <<(std::ostream& os, Shape *& shape);
std::istream& operator >>(std::istream& is, Shape *& shape);

