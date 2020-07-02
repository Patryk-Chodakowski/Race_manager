#ifndef PLAYER_H
#define PLAYER_H

#include "vehicle.h"
#include "team.h"

using namespace std;

class Player
{
    Vehicle *car;
    Team *team;

    Color color;
    string name;
    int id;
    int money = 1000;
    int place = 0;
    int points = 0;

    bool human = false;
    static int instance_number;

public:
    Player(string _names);
    Player(const Player& p);

    void setName(string _name);
//    void setColor(string _color);

    void setPlace(int p);
    void setPoints(int p);

    int getPlace();
    int get_id();
    int getPoints();
    string getName();
    Vehicle* getCar();
    QString getPlayerColorName();

    bool isHuman();

    static int getInstancesNumber();
//    string getColor();

    ~Player();
};

#endif // PLAYER_H
