#include "curve.h"

Curve::Curve()
    : Route_Element()
{

}

Curve::Curve(int r)
    : Route_Element()
{
    radius = r;
}

void Curve::drive()
{

}

void Curve::set_radius(int r)
{
    radius = r;
}

void Curve::set_ends_from_points(Point prev, Point current, Point next)
{

}

