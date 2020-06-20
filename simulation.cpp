#include "simulation.h"

Simulation::Simulation()
{
    road = new Trail();
    road->create_elements();
    contestants = new Car();

    map = new V_Map(road,contestants);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(makeMoves()));
    timer->start(100);
}

Trail* Simulation::get_trail()
{
    return road;
}

Vehicle* Simulation::get_vehicles()
{
    return contestants;
}

V_Map *Simulation::get_map()
{
    return map;
}

void Simulation::setCarsOnStart()
{
    // na razie na punkcie startowym
    Route_Element *elements = road->get_elements();

    contestants->set_route_element(elements);
    contestants->set_position(elements->get_start());
    contestants->set_angle(180);
    contestants->updatePosition();
}

void Simulation::makeMoves()
{
    contestants->drive();

//    contestants->set_position(Point(contestants->get_position().get_x(),contestants->get_position().get_y() + contestants->get_velocity()));
//    contestants->updatePosition();
}

