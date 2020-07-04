#ifndef V_MAP_H
#define V_MAP_H

#include <trail.h>
#include <QGraphicsScene>
#include <QGraphicsItem>

class V_Map
{
    Trail *way;

public:
    V_Map(Trail *trail);
    ~V_Map();

    void draw_map(QGraphicsScene *scene);
    void draw_vehicle(QGraphicsScene *scene,Vehicle *vehicle);
    void removeVehicleFromScene(QGraphicsScene *scene,Vehicle *vehicle);
};

#endif // V_MAP_H
