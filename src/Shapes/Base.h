#pragma once

#include "Shape.h"
#include "Line/Line.h"
#include "Rectangle/Rectangle.h"
#include "Triangle/Triangle.h"
#include "Circle/Circle.h"
#include "Ellipse/Ellipse.h"
#include "Bezier/Bezier.h"

namespace GLPaint::Shapes
{
    bool GetPrimitive(std::string &token, Shape* &shape);
}
