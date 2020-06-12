#ifndef ROUTE_ELEMENT_H
#define ROUTE_ELEMENT_H
#include "point.h"

class Route_Element
{
    Point direction;
    Point start, end;
    Route_Element *next, *prev;
    Route_Element *pit_enter, *pit_exit;
    bool is_pitlane;
public:
    void set_start(Point point);
    void set_end(Point point);
    void set_direction(Point _start, Point _end);
    Point get_dir();
    Point get_start();
    Point get_end();
    virtual void drive();
    Route_Element();
//    ~Route_Element();
};

#endif // ROUTE_ELEMENT_H
