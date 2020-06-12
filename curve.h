#ifndef CURVE_H
#define CURVE_H
#include "route_element.h"

class Curve : public Route_Element
{
    int radius;
    Point centre;
public:
    void drive();
    Curve();
};

#endif // CURVE_H
