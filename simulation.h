#ifndef SIMULATION_H
#define SIMULATION_H

#include <QTimer>
#include <QObject>

#include "car.h"
#include "trail.h"
#include "v_map.h"

class Simulation : public QObject
{
    Q_OBJECT;
    Vehicle *contestants;
    Trail *road;
    V_Map *map;

public:
    Simulation();

    Trail *get_trail();
    Vehicle *get_vehicles();
    V_Map *get_map();

    void setCarsOnStart();

public slots:
    void makeMoves();

};

#endif // SIMULATION_H