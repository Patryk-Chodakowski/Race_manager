#ifndef PLAYER_H
#define PLAYER_H

#include "vehicle.h"
#include "team.h"

using namespace std;

/*!
\brief Klasa gracza/uczestnika gry
*/

class Player
{
    ///wskaźnik na pojazd gracza
    Vehicle *car;

    ///wskaźnik na zespól gracza
    Team *team;

    ///kolor gracza
    Color color;

    ///nazwa gracza
    string name;

    int id;

    ///posiadane pieniądze
    int money = 1000;

    ///pozycja w wyścigu
    int place = 0;

    ///posiadane punkty
    int points = 0;

    ///czy jest człowiekiem
    bool human = false;

    ///licznik instancji klasy
    static int instance_number;

public:
    /*!
    \brief Konstuktor klasy gracza
    \param _names Nazwa gracza
    */
    Player(string _names);
    Player(const Player& p);

    /*!
    \brief Ustawia nazwę gracza
    \param _name Nowa nazwa gracza
    */
    void setName(string _name);

    /*!
    \brief Ustawia pozycję gracza
    \param p Nowa pozycja gracza
    */
    void setPlace(int p);
    /*!
    \brief Ustawia punkty gracza
    \param p Nowe punkty gracza
    */
    void setPoints(int p);
    /*!
    \brief Ustawia liczbę pieniędzy gracza
    \param m Nowy stan konta gracza
    */
    void changeMoney(int m);

    /*!
    \brief Zwraca stan konta gracza
    */
    int getMoney();

    /*!
    \brief Zwraca pozycję gracza
    */
    int getPlace();

    /*!
    \brief Zwraca numer instancji gracza
    */
    int get_id();

    /*!
    \brief Zwraca punkty gracza
    */
    int getPoints();

    /*!
    \brief Zwraca koszt ulepszenia pojazdu gracza
    */
    int vehicleUpgradeCost();

    /*!
    \brief Zwraca koszt ulepszenia zespołu gracza
    */
    int teamUpgradeCost();

    /*!
    \brief Zwraca nazwę gracza
    */
    string getName();

    /*!
    \brief Zwraca wskaźnik na zespół gracza
    */
    Team *getTeam();

    /*!
    \brief Zwraca wskaźnik na pojazd gracza
    */
    Vehicle* getCar();

    /*!
    \brief Zwraca angielską nazwę koloru gracza gracza
    */
    QString getPlayerColorName();

    /*!
    \brief Zwraca czy uczestnik jest człowiekiem (sterowanym graczem)
    */
    bool isHuman();

    /*!
    \brief Zwraca liczbę instancji klasy
    */
    static int getInstancesNumber();

    ~Player();
};

#endif // PLAYER_H
