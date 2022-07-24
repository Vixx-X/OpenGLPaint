#pragma once

#include "../Shape.h"

class Ellipse : public Shape
{
    private:
        Vec4 m_coords;

    public:

        Ellipse() : Shape() { }
        Ellipse(float r, float g, float b) : Shape(r, g, b) { }

        void Set(int x0, int y0, int x1, int y1);

        void Render() override;
        void HardwareRender() override;

        bool OnClick(int x, int y) override;
        void OnMove(int x, int y) override;

        virtual std::ostream& Write(std::ostream& os) const override;
        virtual std::istream& Read(std::istream& is) override;

        void ui(bool allowFiller = true) override;

        std::string to_string() const override;
};