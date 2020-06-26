#include "v_map.h"

V_Map::V_Map(Trail *trail)
{
    way = trail;

//    vehicles = _vehicles;

    std::cout<< "utworzono sciezke" << std::endl;
}

//V_Map::~V_Map()
//{
//    delete way;
//}

void V_Map::draw_map(QGraphicsScene *scene)
{
    Route_Element *elements = way->get_elements();

    scene->addItem(elements->get_graphic_item());
    elements = elements->get_next_element();

    while(!elements->get_finish_line()){
        scene->addItem(elements->get_graphic_item());

        if(elements->get_turn_to_pitlane()){
            Route_Element *pitlane = elements->get_pitlane_element();
            while(pitlane->get_pitlane()){
                scene->addItem(pitlane->get_graphic_item());
                pitlane = pitlane->get_next_element();
            }
        }
        elements = elements->get_next_element();
    }
}

void V_Map::draw_vehicle(QGraphicsScene *scene,Vehicle *vehicle)
{
    scene->addItem(vehicle->get_graphic_item());
}
