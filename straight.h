#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "route_element.h"

class Straight : public Route_Element
{
public:
    Straight();
    Straight(Point _start, int start_radius,Point _end,int end_radius);

//    Point relocateByTrack(Point source);

    int positionToDistanceProjection(Vehicle *v);

    void placeOnLength(Vehicle *v, int length);
    int get_angle();
    int calculateTrajectory(Vehicle* v,int step);
//    Route_Element* calculateTrajectory(Point& position, int& angle ,int step);
    void log_straight();

};

#endif // STRAIGHT_H
