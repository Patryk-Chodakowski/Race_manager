#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "route_element.h"

class Straight : public Route_Element
{
public:
    Straight();
    Straight(Point _start, int start_radius,Point _end,int end_radius);
    ~Straight();

    int positionToDistanceProjection(Vehicle *v) override;
    void placeOnLength(Vehicle *v, int length) override;
    int get_angle() override;
    int calculateTrajectory(Vehicle* v,int step) override;

    void log_straight();
    void log() override;

};

#endif // STRAIGHT_H
