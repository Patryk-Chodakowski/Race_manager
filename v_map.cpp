#include "v_map.h"

V_Map::V_Map(Trail *trail)
{
    way = trail;
}

V_Map::~V_Map()
{

}

void V_Map::draw_map(QGraphicsScene *scene)
{
    Route_Element *elements = way->get_elements();

    scene->setBackgroundBrush(QBrush(Qt::darkGreen, Qt::SolidPattern));

    scene->addItem(elements->get_graphic_item());
    //rysowanie linii mety
    QGraphicsLineItem *line = new QGraphicsLineItem(elements->get_start().get_x(),
                                                    elements->get_start().get_y(),
                                                    elements->get_start().get_x() + 5*elements->get_dir().get_x(),
                                                    elements->get_start().get_y() + 5*elements->get_dir().get_y()
                                                    );

    line->setPen(QPen(Qt::black,elements->getWidth(),Qt::SolidLine,Qt::FlatCap));
    scene->addItem(line);
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

void V_Map::removeVehicleFromScene(QGraphicsScene *scene,Vehicle *vehicle)
{
    scene->removeItem(vehicle->get_graphic_item());
}
