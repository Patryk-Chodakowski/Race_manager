#ifndef GAME_H
#define GAME_H

#include "simulation.h"

class Game
{
    vector<Player*> players;
    Simulation *simulation = nullptr;

public:
    Game();
    ~Game();

    vector<Player*> *getPlayers();
    Player *getHuman();
    int currentRaceNumber = 1;
    int raceLimit = 2;

    string getRaceName();

    void nextRace();
    int getCurrRace();
    int getRaceLimit();
    void createPlayer(string name);
    void prepareSimulation();
    void deleteSimulation();
    Simulation* getSimulation();
};

#endif // GAME_H
