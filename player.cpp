#include "player.h"


Player::Player(string _name)
{
    if(instance_number >= 4) throw std::length_error("Dodano juz maksymalna liczbe graczy");

    instance_number++;
    human = false;

    if (instance_number == 1) human = true;

    name = _name;
    id = instance_number;

    int tank = 0;
    int engineer = 0;

    switch (instance_number) {
    case 1:
        color = Color::RED;
        break;
    case 2:
        color = Color::BLACK;
        tank = 1;
        engineer = 1;
        break;
    case 3:
        color = Color::YELLOW;
        tank = 1;
        engineer = 0;
        break;
    case 4:
        color = Color::GREEN;
        tank = 0;
        engineer = 0;
        break;
    default:
        color = Color::GREEN;
        break;
    }

    team = new Team(engineer);

    if (!human) car = new Vehicle(color,tank,team);
    else car = new Vehicle(color);
}

Player::Player(const Player &p)
{
    instance_number++;
    name = p.name;
    id = p.id;
    color = p.color;
    car = new Vehicle(*(p.car));
}

void Player::setName(string _name)
{
    name = _name;
}

void Player::setPlace(int p)
{
    place = p;
}

void Player::setPoints(int p)
{
    points = p;
}

void Player::changeMoney(int m)
{
    money = m;
}

int Player::getMoney()
{
    return money;
}

int Player::getPlace()
{
    return  place;
}

int Player::get_id()
{
    return id;
}

int Player::getPoints()
{
    return points;
}

int Player::vehicleUpgradeCost()
{
    int cost = 0;
    cost = 500 + car->getTankUpgrage()*200;
    return cost;
}

int Player::teamUpgradeCost()
{
    int cost = 0;
    cost = 500 + team->getEngineers()*200;
    return cost;
}

string Player::getName()
{
    return name;
}

Team *Player::getTeam()
{
    return team;
}

Vehicle *Player::getCar()
{
    return car;
}

QString Player::getPlayerColorName()
{
    return getColorName(color);
}

bool Player::isHuman()
{
    return human;
}

int Player::getInstancesNumber()
{
    return instance_number;
}

Player::~Player()
{
    delete team;
    delete car;

    instance_number--;
}
