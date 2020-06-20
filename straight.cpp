#include "straight.h"

Straight::Straight()
    : Route_Element()
{

}

Straight::Straight(Point _start, int start_radius,Point _end,int end_radius)
{
    set_direction(_start,_end);
    Point dir = get_dir();

    Point s(_start.get_x()+dir.get_x()*start_radius,_start.get_y()+dir.get_y()*start_radius);
    Point e(_end.get_x()-dir.get_x()*end_radius,_end.get_y()-dir.get_y()*end_radius);

    set_start(s);
    set_end(e);

    length = abs(s.get_x() - e.get_x()) + abs(s.get_y() - e.get_y());

    item = new QGraphicsLineItem((qreal) s.get_x(),(qreal) s.get_y(),(qreal) e.get_x(),(qreal) e.get_y());
}

void Straight::log_straight()
{
    std::cout << "line " << length << std::endl;
    get_dir().log_point();
    std::cout << "start: ";
    get_start().log_point();
    std::cout << "end: ";
    get_end().log_point();
}

int Straight::calculateTrajectory(int step)
{
    std::cout << "Prosta" << std::endl;
}
