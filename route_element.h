#ifndef ROUTE_ELEMENT_H
#define ROUTE_ELEMENT_H
#include "point.h"

#include <QGraphicsItem>
#include "qgraphicsarcitem.h"

class Route_Element
{
    Point direction;
    Point start, end;
    Route_Element *next, *prev;
    Route_Element *pitlane_element;

    bool is_pitlane;
    bool is_turn_to_pitlane;
    bool pit_start;
    bool pit_end;

protected:
    QGraphicsItem *item;

public:
    void set_start(Point point);
    void set_end(Point point);
    void set_direction(Point _start, Point _end);

    void set_next(Route_Element *element);
    void set_prev(Route_Element *element);
    void set_pitlane_element(Route_Element *element);

    void set_pitlane();
    void set_turn_to_pitlane();
    void set_pit_start();
    void set_pit_end();

    bool get_pitlane();
    bool get_turn_to_pitlane();
    bool get_pit_start();
    bool get_pit_end();

    Route_Element* get_next_element();
    Route_Element* get_prev_element();
    Route_Element* get_pitlane_element();

    Point get_dir();
    Point get_start();
    Point get_end();
    virtual void drive();
    Route_Element();
//    ~Route_Element();

    QGraphicsItem* get_graphic_item();

};

#endif // ROUTE_ELEMENT_H
