#ifndef PLAYER_H
#define PLAYER_H

#include "vehicle.h"

using namespace std;

class Player
{
    Vehicle *car;
    Color color;
    string name;
    int id;

    static int instance_number;

public:
    Player(string _name);
    Player(const Player& p);

    void setName(string _name);
//    void setColor(string _color);

    int get_id();
    string getName();

    static int getInstancesNumber();
//    string getColor();

    ~Player();
};

#endif // PLAYER_H