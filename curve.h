#ifndef CURVE_H
#define CURVE_H
#include "route_element.h"

class Curve : public Route_Element
{
    int radius;
    Point centre;
public:
    void drive();
    void set_radius(int r);
    void set_ends_from_points(Point prev, Point current, Point next);
    Curve();
    Curve(int r);
};

#endif // CURVE_H
