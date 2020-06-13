#include "point.h"

Point::Point()
{

}

Point::Point(int _x,int _y)
{
    x = _x;
    y = _y;
}

void Point::set_x(int _x)
{
    x = _x;
}

void Point::set_y(int _y)
{
    y = _y;
}

int Point::get_x()
{
    return x;
}

int Point::get_y()
{
    return y;
}

Point Point::direction_vector(Point destination)
{
    int dir_x,dir_y,dx,dy;
    dx = destination.get_x() - x;
    dy = destination.get_y() - y;

    if(dx < 0) dir_x = -1;
    if(dx == 0) dir_x = 0;
    if(dx > 0) dir_x = 1;

    if(dy < 0) dir_y = -1;
    if(dy == 0) dir_y = 0;
    if(dy > 0) dir_y = 1;

    Point result(dir_x,dir_y);
    return result;
}

void Point::log_point()
{
    std::cout << "(" << x << "," << y << ")" << std::endl;
}



int ArcQuaterFromPoint(Point start, Point centre, Point end)
{
    if(start.get_x() < end.get_x()){

    }
    else{

    }
}
