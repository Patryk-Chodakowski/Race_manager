#ifndef ROUTE_ELEMENT_H
#define ROUTE_ELEMENT_H

#include <QGraphicsItem>

#include "qgraphicsarcitem.h"
#include "vehicle.h"
#include "point.h"

class Vehicle;

class Route_Element
{
protected:
    Point direction;
    Point start, end;
    int length;
    int interspace;
    Route_Element *next = nullptr, *prev = nullptr;
    Route_Element *pitlane_element = nullptr;

    bool is_inner = false;
    bool is_pitlane;
    bool is_turn_to_pitlane = false;
    bool pit_start = false;
    bool pit_end = false;
    bool is_finish_line = false;

    QGraphicsItem *item;

public:
    void set_start(Point point);
    void set_end(Point point);
    void set_direction(Point _start, Point _end);

    void set_next(Route_Element *element);
    void set_prev(Route_Element *element);
    void set_pitlane_element(Route_Element *element);

    void set_inner();
    void set_pitlane();
    void set_turn_to_pitlane();
    void set_pit_start();
    void set_pit_end();
    void set_finish_line();
    void set_interspace(int space);

    int get_interspace();
    bool get_pitlane();
    bool get_turn_to_pitlane();
    bool get_pit_start();
    bool get_pit_end();
    bool get_finish_line();
    bool get_inner();

    int get_length();

    Route_Element* get_next_element();
    Route_Element* get_prev_element();
    Route_Element* get_pitlane_element();

    Point get_dir();
    Point get_start();
    Point get_end();

    //rozbic na pozycje, kat, krok
    virtual int calculateTrajectory(Vehicle* v,int step);
//    virtual Route_Element* calculateTrajectory(Point& position, int& angle ,int step);

    Route_Element();
//    ~Route_Element();

    QGraphicsItem* get_graphic_item();

};



#endif // ROUTE_ELEMENT_H
