#include "player.h"


Player::Player(string _name)
{
    if(instance_number >= 4) throw std::length_error("Dodano juz maksymalna liczbe graczy");

    instance_number++;

    cout << "gracz " <<  instance_number << " " << _name << endl;

    name = _name;
    id = instance_number;

    switch (instance_number) {
    case 1:
        color = Color::RED;
        break;
    case 2:
        color = Color::BLACK;
        break;
    case 3:
        color = Color::YELLOW;
        break;
    case 4:
        color = Color::GREEN;
        break;
    default:
        break;
    }
    car = new Vehicle(color);
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

int Player::get_id()
{
    return id;
}

//void Player::setColor(string _color)
//{
//    color = _color;
//}

string Player::getName()
{
    return name;
}

int Player::getInstancesNumber()
{
    return instance_number;
}

//string Player::getColor()
//{
//    return color;
//}

Player::~Player()
{
    instance_number--;
    cout << "usuwam " << name << " " << instance_number << endl;
}
