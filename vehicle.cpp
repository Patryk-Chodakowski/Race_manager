#include "vehicle.h"

Vehicle::Vehicle()
{

}

void Vehicle::set_position(Point _position)
{
    position = _position;
}

void Vehicle::set_angle(double value)
{
    angle = value;
}

Point Vehicle::get_position()
{
    return position;
}

double Vehicle::get_angle()
{
    return angle;
}

QGraphicsItem *Vehicle::get_graphic_item()
{
    return model;
}
