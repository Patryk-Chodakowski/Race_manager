#ifndef STRAIGHT_H
#define STRAIGHT_H
#include "route_element.h"

class Straight : public Route_Element
{
public:
    void drive();
    Straight();
};

#endif // STRAIGHT_H
