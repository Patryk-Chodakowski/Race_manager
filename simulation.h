#ifndef SIMULATION_H
#define SIMULATION_H

#include <QTimer>
#include <QObject>

#include "trail.h"
#include "v_map.h"
#include "player.h"

class Simulation : public QObject
{
    Q_OBJECT;

    vector<Player*> *pv;

    Vehicle *contestants;
    Trail *road;
    V_Map *map;
    int sample_time = 20;

public:
    Simulation(vector<Player*>& players);

    Trail *get_trail();
    Vehicle *get_vehicles();
    V_Map *get_map();
    QTimer *timer;

    void setVehiclesOnStart();
//    void moveVehicles();

public slots:
    void makeMoves();

};

#endif // SIMULATION_H
