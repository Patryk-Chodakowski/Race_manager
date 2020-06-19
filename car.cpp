#include "car.h"

Car::Car()
    :Vehicle()
{
    QPixmap item("yellow_car");
    item = item.scaled(40,60,Qt::KeepAspectRatio);
    model = new QGraphicsPixmapItem(item);
    model->setTransformOriginPoint(20,30);

    model->setX(100);
    model->setY(100);
}
