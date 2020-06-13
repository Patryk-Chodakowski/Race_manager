#ifndef V_MAP_H
#define V_MAP_H

#include <trail.h>
#include <QGraphicsScene>
#include <QGraphicsItem>

class V_Map
{
    Trail *way;
public:
    V_Map();
//    ~V_Map();
    void drow_map(QGraphicsScene *scene);
};

#endif // V_MAP_H
