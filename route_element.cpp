#include "route_element.h"

Route_Element::Route_Element()
{
//    prev = NULL;
//    next = NULL;
//    pitlane_element = NULL;

    is_pitlane = false;
//    is_turn_to_pitlane = false;
//    pit_start = false;
//    pit_end = false;
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

void Route_Element::set_pitlane()
{
    is_pitlane = true;
}

void Route_Element::set_turn_to_pitlane()
{
    is_turn_to_pitlane = true;
}

void Route_Element::set_pit_start()
{
    pit_start = true;
}

void Route_Element::set_pit_end()
{
    pit_end = true;
}

void Route_Element::set_finish_line()
{
    is_finish_line = true;
}

void Route_Element::set_interspace(int space)
{
    interspace = space;
}

int Route_Element::get_interspace()
{
    return interspace;
}

bool Route_Element::get_pitlane()
{
    std::cout<< "zwracam pit "<< is_pitlane <<std::endl;
    return is_pitlane;
}

bool Route_Element::get_turn_to_pitlane()
{
    return is_turn_to_pitlane;
}

bool Route_Element::get_pit_start()
{
    return pit_start;
}

bool Route_Element::get_pit_end()
{
    return pit_end;
}

bool Route_Element::get_finish_line()
{
    return is_finish_line;
}

bool Route_Element::get_inner()
{
    return is_inner;
}

int Route_Element::get_length()
{
    return length;
}

void Route_Element::set_pitlane_element(Route_Element *element)
{
    pitlane_element = element;
}

void Route_Element::set_inner()
{
    is_inner = true;
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
    return pitlane_element;
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

//void Route_Element::test(Vehicle *v)
//{
//    std::cout<< "funkcja testowa bangla " << v->get_angle() << std::endl;
//}

//Route_Element *Route_Element::calculateTrajectory(Point &position, int &angle, int step)
//{

//}

int Route_Element::calculateTrajectory(Vehicle* v,int step){

}

