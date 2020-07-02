#ifndef GAME_H
#define GAME_H

//#include "player.h"
#include "simulation.h"

class Game
{
    vector<Player*> players;
    Simulation *simulation = nullptr;

public:
    Game();
    ~Game();

    void createPlayer(string name);
    void prepareSimulation(int variant = 0);
    Simulation* getSimulation();
};

#endif // GAME_H
