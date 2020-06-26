#include "curve.h"

Curve::Curve()
    : Route_Element()
{

}

Curve::Curve(Point prev, Point current, Point next, int _radius)
    : Route_Element()
{
    this->set_ends_from_points(prev,current,next,_radius);

    item = new QGraphicsArcItem(centre,get_start(),get_end(),_radius);
}

Curve::Curve(int r)
    : Route_Element()
{
    radius = r;
}

int Curve::calculateTrajectory(Vehicle *v, int step)
{
    Point position = v->get_position();
    int angle = v->get_angle();

    Point begin = start;
    Point finish = end;
    Point dir;
    int arcLength = length;
    int arcRadius = radius;

    int start_angle{0}, end_angle{0}, rest(0);
    bool x_from_sin{0}, turn_right{0};
    double z{0};
    int tmp = 1;
    if (is_inner) tmp = -1;

    //wyznaczenie pasa
    if (!is_pitlane){
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

//    std::cout << " curR " << curRadius << " arcR " << arcRadius << " arcL " << arcLength
//              << " dang " << dangle << " abs " << abs(curRadius - arcRadius) << " step " << step << std::endl;

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

    //wyznaczenie pozycji
    if (turn_right){
        angle+=dangle;

        if(angle >= end_angle){
            rest = (angle - end_angle) * arcLength / 90;
            if (end_angle == 360) end_angle = 0;
            angle = end_angle;
            position = finish;
            if (rest == 0) rest++;
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

//    std::cout << " z " << z;
//    position.log_point();
//    centre.log_point();

    return rest;
}

void Curve::set_radius(int r)
{
    radius = r;
}

void Curve::set_ends_from_points(Point prev, Point current, Point next, int _radius)
{
    this->set_direction(prev,next);
    radius = _radius;

    Point dir = prev.direction_vector(current);
    Point s(current.get_x()-dir.get_x()*radius,current.get_y()-dir.get_y()*radius);
    this->set_start(s);

    dir = current.direction_vector(next);
    Point e(current.get_x()+dir.get_x()*radius,current.get_y()+dir.get_y()*radius);
    this->set_end(e);

    length = 1.5 * radius;

    Point c(get_start().get_x()+dir.get_x()*radius,get_start().get_y()+dir.get_y()*radius);
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
