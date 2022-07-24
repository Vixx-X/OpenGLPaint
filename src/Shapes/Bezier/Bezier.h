#pragma once

#include "../Shape.h"
#include <vector>

class Bezier : public Shape
{
    private:
        size_t m_size;
        int m_sample;
        std::vector<Vec2> m_coords;

    public:

        Bezier(size_t N, float r, float g, float b)
            : m_size(N), m_sample(1000), m_coords(N), Shape(r, g, b) { }

        void Set(std::vector<Vec2> new_coords);
        void SetSize(size_t N);

        void Render() override;
        void HardwareRender() override;

        bool OnClick(int x, int y) override;
        void OnMove(int x, int y) override;

        std::ostream& Write(std::ostream& os) const override;
        std::istream& Read(std::istream& is) override;

        void ui(bool allowFiller = true) override;

        std::string to_string() const override;
};
