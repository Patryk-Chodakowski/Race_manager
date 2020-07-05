#include "curve.h"

Curve::Curve(Point<int> prev, Point<int> current, Point<int> next, int _radius)
    : Route_Element()
{
    this->set_ends_from_points(prev,current,next,_radius);
    QGraphicsArcItem *arc = new QGraphicsArcItem(centre,get_start(),get_end(),_radius,width);

    item = arc;
}

Curve::~Curve()
{

}

int Curve::positionToDistanceProjection(Vehicle *v)
{
    return 0;
}

void Curve::placeOnLength(Vehicle *v,int length)
{
    Point<int> begin = start;
    int arcRadius = radius;
    int tmp = 1;
    if (is_inner) tmp = -1;

    switch (v->get_track()) {
    case 1:
        arcRadius = radius + tmp*interspace;
        break;
    case -1:
        arcRadius = radius - tmp*interspace;
        break;
    }

    Point<int> dir = start.direction_vector(centre);
    begin.set_x(centre.get_x() - dir.get_x() * arcRadius);
    begin.set_y(centre.get_y() - dir.get_y() * arcRadius);

    v->set_position(begin);
    v->set_angle(get_angle());

    calculateTrajectory(v,length);
    v->updatePosition();
}

int Curve::get_angle()
{
    int angle = 0;
    switch (quater) {
    case 1:
        if (direction.get_x() <0){
            angle = 0;
        }else{
            angle = 90;
        }
        break;
    case 2:
        if (direction.get_x() <0){
            angle = 270;
        }else{
            angle = 0;
        }
        break;
    case 3:
        if (direction.get_x() <0){
            angle = 270;
        }else{
            angle = 180;
        }
        break;
    case 4:
        if (direction.get_x() <0){
            angle = 180;
        }else{
            angle = 90;
        }
        break;
    }
    return angle;
}

int Curve::calculateTrajectory(Vehicle *v, int step)
{
    Point<int> position = v->get_position();
    int angle = v->get_angle();

    Point<int> begin = start;
    Point<int> finish = end;
    Point<int> dir;
    int arcLength = length;
    int arcRadius = radius;

    int start_angle{0}, end_angle{0}, rest(0);
    bool x_from_sin{0}, turn_right{0};
    double z{0};
    int tmp = 1;
    if (is_inner) tmp = -1;

    Route_Element *bypass = this;
    while (!bypass->get_turn_to_pitlane()) {
        bypass = bypass->get_next_element();
    }
    bypass = bypass->get_next_element();
    int bypass_start = bypass->positionToDistanceProjection(v);

    //wyznaczenie pasa
    if (!is_pitlane || pit_end){
        switch (v->get_track()) {
        case 1:
            arcRadius = radius + tmp*interspace;
            break;
        case -1:
            arcRadius = radius - tmp*interspace;
            break;
        }
    }

    int dradius = 0.5 * step;
    if (dradius == 0) dradius = 1;
    if (step == 0) dradius = 0;
    int curRadius = sqrt(pow((position.get_x() - centre.get_x()),2) + pow((position.get_y() - centre.get_y()),2));

    if (abs(curRadius - arcRadius) <= 2) curRadius = arcRadius;
    else{
        if((curRadius - arcRadius) < 0){
            curRadius += dradius;
        }else{
            curRadius -= dradius;
        }
    }

    arcLength = curRadius * 1.5;
    int dangle =  90 * step / arcLength;

    dir = start.direction_vector(centre);
    begin.set_x(centre.get_x() - dir.get_x() * curRadius);
    begin.set_y(centre.get_y() - dir.get_y() * curRadius);

    dir = end.direction_vector(centre);
    finish.set_x(centre.get_x() - dir.get_x() * curRadius);
    finish.set_y(centre.get_y() - dir.get_y() * curRadius);

    //wyznaczenie luku
    switch (quater) {
    case 1:
        if (direction.get_x() <0){
            turn_right = false;
            start_angle = 360;
            end_angle = 270;
            x_from_sin = false;
        }else{
            turn_right = true;
            start_angle = 90;
            end_angle = 180;
            x_from_sin = true;
        }
        break;
    case 2:
        if (direction.get_x() <0){
            turn_right = false;
            start_angle = 270;
            end_angle = 180;
            x_from_sin = true;
        }else{
            turn_right = true;
            start_angle = 0;
            end_angle = 90;
            x_from_sin = false;
        }
        break;
    case 3:
        if (direction.get_x() <0){
            turn_right = true;
            start_angle = 270;
            end_angle = 360;
            x_from_sin = true;
        }else{
            turn_right = false;
            start_angle = 180;
            end_angle = 90;
            x_from_sin = false;
        }
        break;
    case 4:
        if (direction.get_x() <0){
            turn_right = true;
            start_angle = 180;
            end_angle = 270;
            x_from_sin = false;
        }else{
            turn_right = false;
            start_angle = 90;
            end_angle = 0;
            x_from_sin = true;
        }
        break;
    }

    int distance = dangle;
    bool overgone = false;

    //wyznaczenie pozycji
    if (turn_right){
        angle+=dangle;

        if(angle >= end_angle){
            rest = (angle - end_angle) * arcLength / 90;
            if (end_angle == 360) end_angle = 0;
            angle = end_angle;
            position = finish;
            if (rest == 0) rest++;

            overgone = true;
            distance = dangle - (angle - end_angle);
        }else{
            z = (sin(double((angle - start_angle)*3.14/180))*curRadius);

            if(x_from_sin){
                position.set_x(begin.get_x() + direction.get_x()*z);
                position.set_y(begin.get_y() + direction.get_y()*(curRadius - sqrt(curRadius*curRadius - z*z)));
            }else {
                position.set_x(begin.get_x() + direction.get_x()*(curRadius - sqrt(curRadius*curRadius - z*z)));
                position.set_y(begin.get_y() + direction.get_y()*z);
            }

            rest = 0;
        }
    }else{
        if(angle == 0) angle = 360;
        angle-=dangle;

        if(angle <= end_angle){
            rest = (end_angle - angle) * arcLength / 90;
            angle = end_angle;
            position = finish;
            if (rest == 0) rest++;

            overgone = true;
            distance = dangle - (end_angle - angle);
        }else{
            if(start_angle == 0) start_angle = 360;
            z = (sin(double((start_angle - angle)*3.14/180))*curRadius);

            if(x_from_sin){
                position.set_x(begin.get_x() + direction.get_x()*z);
                position.set_y(begin.get_y() + direction.get_y()*(curRadius - sqrt(curRadius*curRadius - z*z)));
            }else {
                position.set_x(begin.get_x() + direction.get_x()*(curRadius - sqrt(curRadius*curRadius - z*z)));
                position.set_y(begin.get_y() + direction.get_y()*z);
            }
            rest = 0;
        }
    }

    v->set_position(position);
    v->set_angle(angle);

    //wyznaczenie przebytej drogi:
    if(!is_pitlane){    
        v->setDistance(v->getDistance() + (distance*radius/60));
        if (overgone) v->setDistance(lengthSoFar + length);
    }
    else{
        int bypass_end = bypass->positionToDistanceProjection(v);
        v->setDistance(v->getDistance() + (bypass_end - bypass_start));
    }

    return rest;
}

void Curve::log()
{
    log_curve();
}

void Curve::set_radius(int r)
{
    radius = r;
}

void Curve::set_ends_from_points(Point<int> prev, Point<int> current, Point<int> next, int _radius)
{
    this->set_direction(prev,next);
    radius = _radius;

    Point<int> dir = prev.direction_vector(current);
    Point<int> s(current.get_x()-dir.get_x()*radius,current.get_y()-dir.get_y()*radius);
    this->set_start(s);

    dir = current.direction_vector(next);
    Point<int> e(current.get_x()+dir.get_x()*radius,current.get_y()+dir.get_y()*radius);
    this->set_end(e);

    length = 1.5 * radius;

    Point<int> c(get_start().get_x()+dir.get_x()*radius,get_start().get_y()+dir.get_y()*radius);
    centre = c;

    quater = ArcQuaterFromPoint(s,c,e);
}

void Curve::log_curve()
{
    std::cout << "curve: " << length << " " << quater << std::endl;
    if (is_pitlane) std::cout << "pit "  << std::endl;
    else std::cout << " . " << get_pitlane() << std::endl;
    std::cout << "start: ";
    get_start().log_point();
    std::cout << "end: ";
    get_end().log_point();
    std::cout << "centre: ";
    centre.log_point();
    std::cout << "radius: " << radius << std::endl << std::endl;;
}

