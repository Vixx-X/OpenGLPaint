#pragma once

#include <cmath>
#include <ostream>

struct Vec2
{
    float x, y;

    /* Vec2() : x(0.0f), y(0.0f) { } */
    /* Vec2(float _x, float _y) : x(_x), y(_y) { } */

    float dist(const Vec2 &other);

    Vec2 Multiply(const float &other);
    Vec2 Multiply(const Vec2 &other);
    Vec2 operator *(const float &other);
    Vec2 operator *(const Vec2 &other);

    Vec2 Sum(const float &other);
    Vec2 Sum(const Vec2 &other);
    Vec2 operator +(const float &other);
    Vec2 operator +(const Vec2 &other);

};

std::ostream& operator <<(std::ostream& os, Vec2& other);

struct Vec3
{
    union {
        struct
        {
            float x, y, z;
        };
        struct
        {
            float r, g, b;
        };
    };

    Vec3()
        : x(0.0f), y(0.0f), z(0.0f) { }
    Vec3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z) { }
};

struct Vec4
{
    union {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            Vec2 a, b;
        };
    };

    Vec4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    Vec4(float _x, float _y, float _z, float _w)
        : x(_x), y(_y), z(_z), w(_w) { }
};

std::ostream& operator <<(std::ostream& os, Vec4& other);
