#ifndef SIMULATION_H
#define SIMULATION_H

#include "car.h"
#include "trail.h"
#include "v_map.h"

class Simulation
{
    Vehicle *contestants;
    Trail *road;
    V_Map *map;

public:
    Simulation();

    Trail *get_trail();
    Vehicle *get_vehicles();
    V_Map *get_map();

};

#endif // SIMULATION_H
