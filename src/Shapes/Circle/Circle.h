#pragma once

#include "../Ellipse/Ellipse.h"

namespace GLPaint::Shapes
{

    class Circle : public Ellipse
    {
        public:
            Circle() : Ellipse() { }
            Circle(float r, float g, float b) : Ellipse(r, g, b) { }

            std::vector<std::reference_wrapper<float>> GetVertex() override;

            std::ostream& Write(std::ostream& os) const override;
            std::istream& Read(std::istream& is) override;

            void Center(int w, int h) override;

            void ui(bool allowFiller = true) override;

            std::string to_string() const override;
    };

}
