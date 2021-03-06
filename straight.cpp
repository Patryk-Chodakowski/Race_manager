#include "straight.h"

Straight::Straight()
    : Route_Element()
{

}

Straight::Straight(Point<int> _start, int start_radius,Point<int> _end,int end_radius)
{
    set_direction(_start,_end);
    Point<int> dir = get_dir();

    Point<int> s(_start.get_x()+dir.get_x()*start_radius,_start.get_y()+dir.get_y()*start_radius);
    Point<int> e(_end.get_x()-dir.get_x()*end_radius,_end.get_y()-dir.get_y()*end_radius);

    set_start(s);
    set_end(e);

    length = abs(s.get_x() - e.get_x()) + abs(s.get_y() - e.get_y());

    QGraphicsLineItem *line = new QGraphicsLineItem((qreal) s.get_x(),(qreal) s.get_y(),(qreal) e.get_x(),(qreal) e.get_y());
    line->setPen(QPen(Qt::gray,width,Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin));

    item = line;
}

Straight::~Straight()
{

}

int Straight::positionToDistanceProjection(Vehicle *v)
{
    Point<int> result(0,0);
    Point<int> position = v->get_position();

    if(direction.get_x() == 0){
        result.set_x(start.get_x());

        if (direction.get_y() > 0){
            if (position.get_y() < start.get_y()) result.set_y(start.get_y());
            else if((position.get_y() > end.get_y())) result.set_y(end.get_y());
            else result.set_y(position.get_y());
        }else{
            if (position.get_y() > start.get_y()) result.set_y(start.get_y());
            else if((position.get_y() < end.get_y())) result.set_y(end.get_y());
            else result.set_y(position.get_y());
        }
    }else{
        if (direction.get_x() > 0){
            if (position.get_x() < start.get_x()) result.set_x(start.get_x());
            else if((position.get_x() > end.get_x())) result.set_x(end.get_x());
            else result.set_x(position.get_x());
        }else{
            if (position.get_x() > start.get_x()) result.set_x(start.get_x());
            else if((position.get_x() < end.get_x())) result.set_x(end.get_x());
            else result.set_x(position.get_x());
        }
        result.set_y(start.get_y());
    }

    int d = abs(result.get_x() - start.get_x()) + abs(result.get_y() - start.get_y());

    return d;
}

int Straight::calculateTrajectory(Vehicle *v, int step)
{
    Point<int> position = v->get_position();
    Point<int> begin = start;
    Point<int> finish = end;
    int rest = 0;

    Route_Element *bypass = this;
    while (!bypass->get_turn_to_pitlane()) {
        bypass = bypass->get_next_element();
    }
    bypass = bypass->get_next_element();
    int bypass_start = bypass->positionToDistanceProjection(v);


    //wyznaczenie pasa
    if(!is_pitlane){
        switch (v->get_track()) {
        case -1:
            begin.set_x(start.get_x() - direction.get_y()*interspace);
            begin.set_y(start.get_y() + direction.get_x()*interspace);

            finish.set_x(end.get_x() - direction.get_y()*interspace);
            finish.set_y(end.get_y() + direction.get_x()*interspace);
            break;
        case 1:
            begin.set_x(start.get_x() + direction.get_y()*interspace);
            begin.set_y(start.get_y() - direction.get_x()*interspace);

            finish.set_x(end.get_x() + direction.get_y()*interspace);
            finish.set_y(end.get_y() - direction.get_x()*interspace);
            break;
        }
    }

    int diff = 0.5 * step;
    if (diff == 0) diff = 1;
    if (step == 0) diff = 0;

    //zmiana pasa
    if(direction.get_x() == 0){
        if(position.get_x() != begin.get_x()){
            if (position.get_x() - begin.get_x() < 0){
                diff = position.get_x() + diff;
                if (diff > begin.get_x()) diff = begin.get_x();
            }else{
                diff = position.get_x() - diff;
                if (diff < begin.get_x()) diff = begin.get_x();
            }
            position.set_x(diff);

        }else{
            position.set_x(begin.get_x());
        }
        position.set_y(position.get_y() + direction.get_y()*step);
    }else{
        if(position.get_y() != begin.get_y()){
            if (position.get_y() - begin.get_y() < 0){
                diff = position.get_y() + diff;
                if (diff > begin.get_y()) diff = begin.get_y();
            }else{
                diff = position.get_y() - diff;
                if (diff < begin.get_y()) diff = begin.get_y();
            }
            position.set_y(diff);

        }else{
            position.set_y(begin.get_y());
        }
        position.set_x(position.get_x() + direction.get_x()*step);
    }

    //jesli przekroczono element
    if (
            (1 == direction.get_x() && position.get_x() > finish.get_x()) ||
            (-1 == direction.get_x() && position.get_x() < finish.get_x()) ||
            (1 == direction.get_y() && position.get_y() > finish.get_y()) ||
            (-1 == direction.get_y() && position.get_y() < finish.get_y())
       )
    {

        rest = abs( direction.get_x()*(finish.get_x() - position.get_x()) + direction.get_y()*(finish.get_y() - position.get_y()) );

        position.set_x(position.get_x() - direction.get_x()*rest);
        position.set_y(position.get_y() - direction.get_y()*rest);

        v->set_position(position);

        if(!is_pitlane){
            v->setDistance(lengthSoFar + length);
        }
        else{
            int bypass_end = bypass->positionToDistanceProjection(v);
            v->setDistance(v->getDistance() + (bypass_end - bypass_start));
        }

        //wykonanie okrążenia
        if (next->get_finish_line()){
            v->setDistance(0);
            v->incraseLap();
        }
    }else{
        v->set_position(position);

        if(!is_pitlane){
            v->setDistance( v->getDistance() + step);
        }
        else{
            int bypass_end = bypass->positionToDistanceProjection(v);
            v->setDistance(v->getDistance() + (bypass_end - bypass_start));
        }
    }

    return rest;
}

void Straight::log_straight()
{
    std::cout << "line " << length << std::endl;
    if (is_pitlane) std::cout << "pit" << std::endl;
    get_dir().log_point();
    std::cout << "start: ";
    get_start().log_point();
    std::cout << "end: ";
    get_end().log_point();
    std::cout << "lSoFar: " << lengthSoFar  << " length: "<< length ;
    std::cout << std::endl;
}

void Straight::log()
{
    log_straight();
}

int Straight::get_angle(){
    int angle = 0;
    if (direction.get_x() > 0) angle = 90;
    if (direction.get_x() < 0) angle = 270;
    if (direction.get_y() > 0) angle = 180;
    if (direction.get_y() < 0) angle = 0;
    return angle;
}

void Straight::placeOnLength(Vehicle *v, int length){
    Point<int> begin = start;

    switch (v->get_track()) {
    case -1:
        begin.set_x(start.get_x() - direction.get_y()*interspace);
        begin.set_y(start.get_y() + direction.get_x()*interspace);
        break;
    case 1:
        begin.set_x(start.get_x() + direction.get_y()*interspace);
        begin.set_y(start.get_y() - direction.get_x()*interspace);
        break;
    }

    v->set_position(begin);
    v->set_angle(get_angle());

    calculateTrajectory(v,length);
    v->updatePosition();
}
