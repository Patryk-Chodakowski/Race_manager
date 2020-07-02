#include "game.h"


Game::Game()
{

    createPlayer("Andrzej");
    createPlayer("Rafal");
    createPlayer("Szymon");
    createPlayer("Krzysztof");

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

void Game::prepareSimulation(int variant)
{
    string source = "";
    switch (variant) {
        case 0:
            source = "punkty_mapy.txt";
        break;
    default:
        throw std::invalid_argument("Brak zdefiniowanej mapy");
    }

    simulation = new Simulation(players,source);
}

Simulation *Game::getSimulation()
{
    return simulation;
}
