#include "vehicle.h"

Vehicle::Vehicle()
{
    angle = 0;
}

void Vehicle::togglePitStop()
{
    goToPitstop = !goToPitstop;
}

void Vehicle::set_position(Point _position)
{
    position = _position;
}

void Vehicle::set_angle(double value)
{
    angle = value;
}

void Vehicle::set_route_element(Route_Element *element)
{
    current_element = element;
}

void Vehicle::set_track(int track)
{
    currentTrack = track;
}

int Vehicle::get_track()
{
    return currentTrack;
}

Route_Element *Vehicle::get_route_element()
{
    return current_element;
}

Point Vehicle::get_position()
{
    return position;
}

double Vehicle::get_angle()
{
    return angle;
}

void Vehicle::updatePosition()
{
    model->setX(position.get_x() - width/2);
    model->setY(position.get_y() - height/2);
    model->setRotation(angle);
}

int Vehicle::get_velocity()
{
    return velocity;
}

QGraphicsItem *Vehicle::get_graphic_item()
{
    return model;
}

void Vehicle::drive(int step_time)
{
    //wyznacz z parametrow pojazdu skok drogi na jednoske czasu

    //wyznacz predkosc
    velocity += acceleration;
    if (velocity > maxVelocity) velocity = maxVelocity;

    //wyznacz skok
    int step = velocity;

    //przejechana droga
    distance += step;

    step = current_element->calculateTrajectory(this,step);
    while (step != 0){
        std::cout << "pentla" << std::endl;

        if(goToPitstop && current_element->get_turn_to_pitlane()){
            current_element = current_element->get_pitlane_element();
        }else{
            current_element = current_element->get_next_element();
        }

        step = current_element->calculateTrajectory(this,step);
    };
    updatePosition();
}
