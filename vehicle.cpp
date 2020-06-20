#include "vehicle.h"

Vehicle::Vehicle()
{
    angle = 0;
}

void Vehicle::set_position(Point _position)
{
    position = _position;
}

void Vehicle::set_angle(double value)
{
    angle = value;
}

void Vehicle::set_route_element(Route_Element *element)
{
    current_element = element;
}

void Vehicle::drive()
{
    //wyznacz z parametrow pojazdu skok drogi na jednoske czasu


    current_element->calculateTrajectory();
    updatePosition();
}

Route_Element *Vehicle::get_route_element()
{
    return current_element;
}

Point Vehicle::get_position()
{
    return position;
}

double Vehicle::get_angle()
{
    return angle;
}

void Vehicle::updatePosition()
{
    model->setX(position.get_x() - width/2);
    model->setY(position.get_y() - height/2);
    model->setRotation(angle);
}

int Vehicle::get_velocity()
{
    return velocity;
}

QGraphicsItem *Vehicle::get_graphic_item()
{
    return model;
}
