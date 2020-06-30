#include "game.h"


Game::Game()
{

    createPlayer("Andrzej");
    createPlayer("Rafal");
    createPlayer("Szymon");
    createPlayer("Krzysztof");

    simulation = new Simulation(players);
}

Game::~Game()
{
    for (auto& it: players){
        delete it;
    }
}

void Game::createPlayer(string name)
{
    try {
        Player *p = new Player(name);
        players.push_back(p);
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

Simulation *Game::getSimulation()
{
    return simulation;
}
