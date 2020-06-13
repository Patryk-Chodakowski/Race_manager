#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
    int x,y;
public:
    void set_x(int _x);
    void set_y(int _y);
    int get_x();
    int get_y();
    Point direction_vector(Point destination);

    void log_point();

    Point();
    Point(int _x,int _y);
};

int ArcQuaterFromPoint(Point start,Point centre, Point end);

#endif // POINT_H
