#ifndef CURVE_H
#define CURVE_H
#include "route_element.h"
#include <cmath>

class Curve : public Route_Element
{
    int radius;
    int quater;
    Point centre;

public:
    void set_radius(int r);
    void set_ends_from_points(Point prev, Point current, Point next, int _radius);

    void log_curve();

    Point pointOnCurve(int& dAngle);

    Curve();
    Curve(Point prev, Point current, Point next, int _radius);
    Curve(int r);

    int calculateTrajectory(Vehicle* v,int step);
//    Route_Element* calculateTrajectory(Point& position, int& angle ,int step);
};

#endif // CURVE_H
