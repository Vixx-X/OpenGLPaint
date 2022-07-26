#pragma once

#include "../Shape.h"

namespace GLPaint::Shapes
{

    class Rectangle : public Shape
    {
        private:
            Vec4 m_coords;

        public:

            Rectangle(float r, float g, float b) : Shape(r, g, b) { }

            void Set(int x0, int y0, int x1, int y1);
            std::vector<std::reference_wrapper<float>> GetVertex() override;

            void Render() override;
            void HardwareRender() override;

            bool OnClick(int x, int y) override;
            void OnMove(int x, int y) override;
            void Center(int w, int h) override;

            std::ostream& Write(std::ostream& os) const override;
            std::istream& Read(std::istream& is) override;

            void ui(bool allowFiller = true) override;

            std::string to_string() const override;
    };
}
