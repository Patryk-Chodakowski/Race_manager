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
    int width = 80;
    Point direction;
    Point start, end;
    int length;
    int interspace;
    int lengthSoFar = 0;
    Route_Element *next = nullptr, *prev = nullptr;
    Route_Element *pitlane_element = nullptr;

    int pit_speed_limit = 3;
    bool is_inner = false;
    bool is_pitlane = false;
    bool is_turn_to_pitlane = false;
    bool pit_start = false;
    bool pit_end = false;
    bool is_finish_line = false;
    bool curve = false;

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
    void setLengthSoFar(int l);

    int get_interspace();
    int getSpeedLimit();
    bool get_pitlane();
    bool get_turn_to_pitlane();
    bool get_pit_start();
    bool get_pit_end();
    bool get_finish_line();
    bool get_inner();
    bool is_curve();
    int getWidth();

    int get_length();
    int getLengthSoFar();

    Route_Element* get_next_element();
    Route_Element* get_prev_element();
    Route_Element* get_pitlane_element();
    Route_Element* getPitBypass();

    Point get_dir();
    Point get_start();
    Point get_end();

    virtual int positionToDistanceProjection(Vehicle *v);

//    virtual Point relocateByTrack(Point source);
    virtual void placeOnLength(Vehicle *v, int _length);
    virtual int get_angle();
    virtual int calculateTrajectory(Vehicle* v,int step);
    virtual void log();

    Route_Element();
//    ~Route_Element();

    QGraphicsItem* get_graphic_item();

};



#endif // ROUTE_ELEMENT_H
