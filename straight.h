#ifndef STRAIGHT_H
#define STRAIGHT_H
#include "route_element.h"

class Straight : public Route_Element
{
public:
    void drive();
    Straight();
    Straight(Point _start, int start_radius,Point _end,int end_radius);

    void log_straight();

};

#endif // STRAIGHT_H
