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

int Straight::calculateTrajectory(Vehicle *v, int step)
{
    Point position = v->get_position();

    position.set_x(position.get_x() + direction.get_x()*step);
    position.set_y(position.get_y() + direction.get_y()*step);

    //jesli przekroczono element
    if (
            (1 == direction.get_x() && position.get_x() > end.get_x()) ||
            (-1 == direction.get_x() && position.get_x() < end.get_x()) ||
            (1 == direction.get_y() && position.get_y() > end.get_y()) ||
            (-1 == direction.get_y() && position.get_y() < end.get_y())
       )
    {
        step = abs((end.get_x() - position.get_x()) + (end.get_y() - position.get_y()) );
        position = end;
        return step;
    }
    else{
        v->set_position(position);
        return 0;
    }
}

//Route_Element *Straight::calculateTrajectory(Point &position, int &angle, int step)
//{
//    std::cout << "Prosta" << std::endl;
//    return this;
//}

void Straight::log_straight()
{
    std::cout << "line " << length << std::endl;
    if (is_pitlane) std::cout << "pit" << std::endl;
    else std::cout << " . " << is_pitlane << std::endl;
    get_dir().log_point();
    std::cout << "start: ";
    get_start().log_point();
    std::cout << "end: ";
    get_end().log_point();
    std::cout << std::endl;
}
