#include "Vec.h"

float Vec2::dist(const Vec2 &other) {
    float a = x - other.x, b = y - other.y;
    return sqrt(a * a + b * b);
}

Vec2 Vec2::Multiply(const float &other) {
    Vec2 ret;
    ret.x = x * other, ret.y = y * other;
    return ret;
}
Vec2 Vec2::Multiply(const Vec2 &other) {
    Vec2 ret;
    ret.x = x * other.x, ret.y = y * other.y;
    return ret;
}
Vec2 Vec2::operator *(const float &other) { return Multiply(other); }
Vec2 Vec2::operator *(const Vec2 &other) { return Multiply(other); }

Vec2 Vec2::Sum(const float &other) {
    Vec2 ret;
    ret.x = x + other, ret.y = y + other;
    return ret;
}
Vec2 Vec2::Sum(const Vec2 &other) {
    Vec2 ret;
    ret.x = x + other.x, ret.y = y + other.y;
    return ret;
}
Vec2 Vec2::operator +(const float &other) { return Sum(other); }
Vec2 Vec2::operator +(const Vec2 &other) { return Sum(other); }

std::ostream& operator <<(std::ostream& os, Vec2& other)
{
    return os << other.x << "," << other.y;
}

std::ostream& operator <<(std::ostream& os, Vec4& other)
{
    return os << other.a << "," << other.b;
}

