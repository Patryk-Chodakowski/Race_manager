#ifndef ROUTE_ELEMENT_H
#define ROUTE_ELEMENT_H
#include "point.h"

class Route_Element
{
    Point start, end;
    Route_Element *next, *prev;
    bool is_pitlane;
public:
    virtual void drive();
    Route_Element();
//    ~Route_Element();
};

#endif // ROUTE_ELEMENT_H
