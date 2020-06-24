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

    int dangle =  90 * step / length;

//    Point position(pointOnCurve(dangle));

    int start_angle{0}, end_angle{0}, rest(0);
    bool x_from_sin{0}, turn_right{0};
    double z;

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
            end_angle = 180;
            x_from_sin = false;
        }
        break;
    }

    if (turn_right){
        angle+=dangle;

        if(angle >=end_angle){
            rest = (angle - end_angle) * length / 90;
            if (end_angle == 360) end_angle = 0;
            angle = end_angle;
            position = end;
            if (rest == 0) rest++;
        }else{
            z = (sin(double((angle - start_angle)*3.14/180))*radius);

            if(x_from_sin){
                position.set_x(start.get_x() + direction.get_x()*z);
                position.set_y(start.get_y() + direction.get_y()*(radius -sqrt(radius*radius - z*z)));
            }else {
                position.set_x(start.get_x() + direction.get_x()*(radius - sqrt(radius*radius - z*z)));
                position.set_y(start.get_y() + direction.get_y()*z);
            }

            rest = 0;
        }
    }else{
        if(angle == 0) angle = 360;
        angle-=dangle;

        if(angle <= end_angle){
            rest = (end_angle - angle) * length / 90;
            angle = end_angle;
            position = end;
            if (rest == 0) rest++;
        }else{
            if(start_angle == 0) start_angle = 360;
            z = (sin(double((start_angle - angle)*3.14/180))*radius);

            if(x_from_sin){
                position.set_x(start.get_x() + direction.get_x()*z);
                position.set_y(start.get_y() + direction.get_y()*(radius -sqrt(radius*radius - z*z)));
            }else {
                position.set_x(start.get_x() + direction.get_x()*(radius - sqrt(radius*radius - z*z)));
                position.set_y(start.get_y() + direction.get_y()*z);
            }

            rest = 0;

        }
    }

//    position.set_x();

    v->set_position(position);
    v->set_angle(angle);

      std::cout << "luk " << angle << " " << dangle << std::endl;
      return rest;
}

//Route_Element *Curve::calculateTrajectory(Point &position, int &angle, int step)
//{
//    std::cout << "luk" << std::endl;
//    return this;
//}

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

Point Curve::pointOnCurve(int& dAngle)
{

}


