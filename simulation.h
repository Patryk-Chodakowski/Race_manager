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

    Trail *road;
    QTimer *timer;

    vector<Player*> *pv;
    Player *human;

    int currentLap = 0;
    int minDistance = 80;
    int sample_time = 20;

public:
    Simulation(vector<Player*>& players,string sourceFile);
    ~Simulation();

    Trail *get_trail();
    Player *get_human();
    vector<Player*> *getPlayers();

    void setVehiclesOnStart();

    void checkPositionBetweenVehicles();
    void checkPlayersPlace();

    void simStart();
    void simPause();

    void raceEnd();
    int getCurrentLap();

public: signals:
    void updateView();
    void closeSimWindow();

    void disablePitButton();
    void enablePitButton();

    void raceEnded();

public slots:
    void makeMoves();
};

#endif // SIMULATION_H
