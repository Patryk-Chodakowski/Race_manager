#ifndef SIMULATION_H
#define SIMULATION_H

#include <QTimer>
#include <QObject>
#include <iomanip>

#include "trail.h"
#include "v_map.h"
#include "player.h"

class Simulation : public QObject
{
    Q_OBJECT;

    vector<Player*> *pv;

    Player *human;
    Trail *road;
    int currentLap = 0;

    int minDistance = 80;

//    V_Map *map;
    int sample_time = 20;

public:
    Simulation(vector<Player*>& players,string sourceFile);

    Trail *get_trail();
    Player *get_human();
//    V_Map *get_map();
    vector<Player*> *getPlayers();

    QTimer *timer;

    void setVehiclesOnStart();
    void checkPositionBetweenVehicles();
    void checkPlayersPlace();

    void simStart();
    void simPause();

    void raceEnd();
    int getCurrentLap();
//    void moveVehicles();

public: signals:
    void updateView();
    void closeSimWindow();

    void disablePitButton();
    void enablePitButton();

public slots:
    void makeMoves();

};

#endif // SIMULATION_H
