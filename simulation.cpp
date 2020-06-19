#include "simulation.h"

Simulation::Simulation()
{
    road = new Trail();
    road->create_elements();
    contestants = new Car();

    map = new V_Map(road,contestants);
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
