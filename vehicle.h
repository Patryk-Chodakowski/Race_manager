#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsItem>
#include "route_element.h"

class Vehicle
{
    friend class Route_Element;

protected:
    Point position;
    double angle;
    int width,height;
    int velocity;
    int distance;
    Route_Element *current_element;

    QGraphicsItem *model;

public:
    Vehicle();

    void set_position(Point _position);
    void set_angle(double value);
    void set_route_element(Route_Element *element);

    void drive();

    Route_Element* get_route_element();
    Point get_position();
    double get_angle();
    void updatePosition();
    int get_velocity();

    QGraphicsItem * get_graphic_item();
};

#endif // VEHICLE_H
