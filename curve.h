#ifndef CURVE_H
#define CURVE_H
#include "route_element.h"

class Curve : public Route_Element
{
    int radius;
    Point centre;
public:
    int calculateTrajectory(int step = 0);
    void set_radius(int r);
    void set_ends_from_points(Point prev, Point current, Point next, int _radius);

    void log_curve();

    Curve();
    Curve(Point prev, Point current, Point next, int _radius);
    Curve(int r);
};

#endif // CURVE_H
