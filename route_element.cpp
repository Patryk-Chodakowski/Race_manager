#include "route_element.h"

Route_Element::Route_Element()
{

}

QGraphicsItem *Route_Element::get_graphic_item()
{
    return item;
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

void Route_Element::set_next(Route_Element *element)
{
    next = element;
}

void Route_Element::set_prev(Route_Element *element)
{
    prev = element;
}

void Route_Element::set_pitlane(Route_Element *element)
{
    pitlane = element;
}

Route_Element *Route_Element::get_next_element()
{
    return next;
}

Route_Element *Route_Element::get_prev_element()
{
    return prev;
}

Route_Element *Route_Element::get_pitlane_element()
{
    return pitlane;
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


