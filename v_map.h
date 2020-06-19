#ifndef V_MAP_H
#define V_MAP_H

#include <trail.h>
#include "car.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

class V_Map
{
    Trail *way;
    Vehicle *vehicles;

public:
    V_Map(Trail *trail, Vehicle *_vehicles);
//    ~V_Map();
    void draw_map(QGraphicsScene *scene);
    void draw_vehicle(QGraphicsScene *scene);
};

#endif // V_MAP_H
