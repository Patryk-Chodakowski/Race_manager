#include "simulation.h"

Simulation::Simulation(vector<Player*>& players)
{
    pv = &players;

    road = new Trail();
    road->create_elements();
    human = players.at(0);

//    map = new V_Map(road);
//    map->draw_vehicle();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(makeMoves()));
    timer->start(sample_time);
}

Trail* Simulation::get_trail()
{
    return road;
}

Player* Simulation::get_human()
{
    return human;
}

vector<Player *> *Simulation::getPlayers()
{
    return pv;
}

//V_Map *Simulation::get_map()
//{
////    return map;
//}

void Simulation::setVehiclesOnStart()
{
      Route_Element *element = road->get_elements()->get_prev_element();

      int distance = 40;
      int pos = element->get_length() - distance;
      int track = -1;

      for(auto& player: (*pv)){
          player->getCar()->set_route_element(element);
          player->getCar()->set_track(track);
          player->getCar()->setOvertake(true);
          element->placeOnLength(player->getCar(),pos);

          pos -= distance;
          track *= (-1);
      }
}

void Simulation::makeMoves()
{
//    contestants->drive(sample_time);

    std::cout << "krok" << std::endl;

      for(auto& player: (*pv)){
          std::cout << "ruch " <<  player->getName() << std::endl;
          player->getCar()->drive(sample_time);
      }


//    contestants->set_position(Point(contestants->get_position().get_x(),contestants->get_position().get_y() + contestants->get_velocity()));
//    contestants->updatePosition();
}

