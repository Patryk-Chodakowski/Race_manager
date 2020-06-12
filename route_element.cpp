#include "route_element.h"

Route_Element::Route_Element()
{

}

void Route_Element::set_start(Point point)
{
    start = point;
}

void Route_Element::set_end(Point point)
{
    end = point;
}

void Route_Element::set_direction(Point from, Point to)
{
    direction = from.direction_vector(to);
}

Point Route_Element::get_dir()
{
    return direction;
}

Point Route_Element::get_start()
{
    return start;
}

Point Route_Element::get_end()
{
    return end;
}

void Route_Element::drive()
{

}


