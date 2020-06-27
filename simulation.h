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

    Player *human;
    Trail *road;

//    V_Map *map;
    int sample_time = 20;

public:
    Simulation(vector<Player*>& players);

    Trail *get_trail();
    Player *get_human();
//    V_Map *get_map();
    vector<Player*> *getPlayers();

    QTimer *timer;

    void setVehiclesOnStart();
//    void moveVehicles();

public slots:
    void makeMoves();

};

#endif // SIMULATION_H
