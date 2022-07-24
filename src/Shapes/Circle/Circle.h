#pragma once

#include "../Ellipse/Ellipse.h"

class Circle : public Ellipse
{
    private:
        Vec4 m_coords;

    public:

        Circle() : Ellipse() { }
        Circle(float r, float g, float b) : Ellipse(r, g, b) { }

        std::ostream& Write(std::ostream& os) const override;
        std::istream& Read(std::istream& is) override;

        void ui(bool allowFiller = true) override;

        std::string to_string() const override;
};
