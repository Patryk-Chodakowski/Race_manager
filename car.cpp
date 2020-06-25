#include "car.h"

Car::Car()
    :Vehicle()
{
    width =  40;
    height = 60;
    velocity = 0;
    maxVelocity = 5;
    acceleration = 1;

    QPixmap item("yellow_car");
    item = item.scaled(width,height,Qt::KeepAspectRatio);
    model = new QGraphicsPixmapItem(item);
    model->setTransformOriginPoint(model->boundingRect().center());

}
