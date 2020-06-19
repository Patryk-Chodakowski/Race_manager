#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsItem>
#include "point.h"

class Vehicle
{
    Point position;
    double angle;



protected:
    QGraphicsItem *model;

public:
    Vehicle();

    void set_position(Point _position);
    void set_angle(double value);
    Point get_position();
    double get_angle();

    QGraphicsItem * get_graphic_item();


};

#endif // VEHICLE_H
