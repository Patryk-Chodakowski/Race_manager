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
    for(auto& it: players){
        delete it;
    }

    while(!players.empty()){
        players.pop_back();
    }
}

vector<Player*> *Game::getPlayers()
{
    return &players;
}

Player *Game::getHuman()
{
    return players.at(0);
}

string Game::getRaceName()
{
    string name = "";
    switch (currentRaceNumber) {
        case 0:
            name = "GP Monaco";
        break;
        case 1:
            name = "GP France";
            break;
        default:
            throw std::invalid_argument("Brak zdefiniowanej mapy");
    }
    return name;
}

void Game::nextRace()
{
    currentRaceNumber++;
}

int Game::getCurrRace()
{
    return currentRaceNumber;
}

int Game::getRaceLimit()
{
    return raceLimit;
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

void Game::prepareSimulation()
{
    string source = "";
    int laps = 0;
    string name = "";

    name = getRaceName();

    switch (currentRaceNumber) {
        case 0:
            source = "punkty_mapy.txt";
            laps = 4;
        break;
    case 1:
        source = "mapa_2.txt";
        laps = 3;
        break;
    default:
        throw std::invalid_argument("Brak zdefiniowanej mapy");
    }

    simulation = new Simulation(players,source);
    simulation->get_trail()->setLaps(laps);
    simulation->get_trail()->setName(name);
}

void Game::deleteSimulation()
{
    simulation->~Simulation();
}

Simulation *Game::getSimulation()
{
    return simulation;
}
