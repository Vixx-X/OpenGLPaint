#include "Base.h"
#include <string>

namespace GLPaint::Shapes
{
    bool GetPrimitive(std::string &token, Shape* &shape)
    {
        bool filled = false;
        if (token.rfind("FILLED_", 0) == 0) {
            filled = true;
            token = token.substr(7);
        }

        if (token == "LINE")
            shape = new Line(0, 0, 0);
        else if (token == "RECTANGLE")
            shape = new Rectangle(0, 0, 0);
        else if (token == "TRIANGLE")
            shape = new Triangle(0, 0, 0);
        else if (token == "ELLIPSE")
            shape = new Ellipse();
        else if (token == "CIRCLE")
            shape = new Circle(0, 0, 0);
        else if (token.rfind("BEZIER", 0) == 0) {
            int N = stoi(token.substr(6));
            shape = new Bezier(N, 0, 0, 0);
        }

        if (!shape)
            return false;

        shape->SetFill(filled);

        return true;
    }
}
