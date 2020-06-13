#include "v_map.h"

V_Map::V_Map()
{
    way = new Trail();
    way->create_elements();
    std::cout<< "utworzono sciezke" << std::endl;
}

//V_Map::~V_Map()
//{
//    delete way;
//}

void V_Map::drow_map(QGraphicsScene *scene)
{
    Route_Element *elements = way->get_elements();

    while(elements->get_next_element() != NULL){
        scene->addItem(elements->get_graphic_item());
        elements = elements->get_next_element();
    }
    scene->addItem(elements->get_graphic_item());
}
