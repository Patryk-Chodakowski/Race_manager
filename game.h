#ifndef GAME_H
#define GAME_H

#include "simulation.h"

/*!
\brief Klasa rozgrywki, sterująca grą
*/

class Game
{
    ///wektor graczy/uczestników
    vector<Player*> players;
    ///wskaźnik symulacji/wyścigu
    Simulation *simulation = nullptr;

    ///aktualny wyscig
    int currentRaceNumber = 0;
    ///liczba wyscigów w grze
    int raceLimit = 2;
public:
    Game();
    ~Game();

    /*!
    \brief Umożliwia dostęp do graczy biorących udział w grze
    \return Wskaźnik na wektor wskaźników na graczy
    */
    vector<Player*> *getPlayers();

    /*!
    \brief Dostęp do sterowanego gracza
    \return wstaźnik na sterowanego gracza;
    */
    Player *getHuman();

    /*!
    \brief Dostęp do nazwy wyścigu
    \return nazwa najbliższego wyścigu
    */
    string getRaceName();

    /*!
    \brief Przejście do kolejnego wyścigu
    */
    void nextRace();

    /*!
    \brief Zwraca numer aktualnego wyścigu
    */
    int getCurrRace();

    /*!
    \brief Zwraca liczbę wyścigów w grze
    */
    int getRaceLimit();

    /*!
    \brief Zwraca pozycję gracza w rankingu
    */
    int getHumanStanding();

    /*!
    \brief Tworzy nowego gracza i dodaje do wektora graczy
    \param name Nazwa gracza
    */
    void createPlayer(string name);

    /*!
    \brief Tworzy obiekt symulacji z aktualnym wyścigiem
    */
    void prepareSimulation();

    /*!
    \brief Usuwa obiekt symulacji z aktualnym wyścigiem
    */
    void deleteSimulation();

    /*!
    \brief Zwraca wskaźnik na obiekt symulacji z aktualnym wyścigiem
    */
    Simulation* getSimulation();
};

#endif // GAME_H
