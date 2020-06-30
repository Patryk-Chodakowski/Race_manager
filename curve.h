#ifndef CURVE_H
#define CURVE_H

#include <cmath>

#include "route_element.h"


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

//    Point relocateByTrack(Point source);

    int positionToDistanceProjection(Vehicle *v) override;

    void placeOnLength(Vehicle *v, int length) override;
    int get_angle() override;
    int calculateTrajectory(Vehicle* v,int step) override;
    void log() override;
};

#endif // CURVE_H
