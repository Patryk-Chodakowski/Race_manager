#include "curve.h"

Curve::Curve()
    : Route_Element()
{

}

Curve::Curve(Point prev, Point current, Point next, int _radius)
    : Route_Element()
{
    this->set_ends_from_points(prev,current,next,_radius);

    item = new QGraphicsArcItem(centre,get_start(),get_end(),_radius);
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

void Curve::set_ends_from_points(Point prev, Point current, Point next, int _radius)
{
    this->set_direction(prev,next);
    radius = _radius;

    Point dir = prev.direction_vector(current);
    Point s(current.get_x()-dir.get_x()*radius,current.get_y()-dir.get_y()*radius);
    this->set_start(s);

    dir = current.direction_vector(next);
    Point e(current.get_x()+dir.get_x()*radius,current.get_y()+dir.get_y()*radius);
    this->set_end(e);

    Point c(get_start().get_x()+dir.get_x()*radius,get_start().get_y()+dir.get_y()*radius);
    centre = c;
}

void Curve::log_curve()
{
    std::cout << "curve: " << std::endl;
    std::cout << "start: ";
    get_start().log_point();
    std::cout << "end: ";
    get_end().log_point();
    std::cout << "centre: ";
    centre.log_point();
    std::cout << "radius: " << radius << std::endl;
}



