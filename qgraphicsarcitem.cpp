#include "qgraphicsarcitem.h"

QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent)
    :QGraphicsItem()
{
    QRectF rec(x,y,radius,radius);
    build_rectanlge = rec;
    quater = 0;
}

QGraphicsArcItem::QGraphicsArcItem(Point centre, Point start, Point end, int radius)
    :QGraphicsItem()
{
    //rysowanie luku ze sprawdzeniem strony

    Point dir = centre.direction_vector(end);



//    Point dir = prev.direction_vector(current);
//    Point s(current.get_x()-dir.get_x()*radius,current.get_y()-dir.get_y()*radius);
//    this->set_start(s);

//    dir = current.direction_vector(next);
//    Point e(current.get_x()+dir.get_x()*radius,current.get_y()+dir.get_y()*radius);
//    this->set_end(e);


    QRectF rec = QRectF(centre.get_x() - radius,centre.get_y() - radius,2*radius,2*radius);
    build_rectanlge = rec;
}

QRectF QGraphicsArcItem::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = build_rectanlge;
    QBrush brush(Qt::black);

    int start_angle = 0;
    if (quater != 0){
        start_angle = (quater-1)*90 * 16;
    }
    int end_angle = 90 * 16;

    painter->drawArc(rec,start_angle,end_angle);
}

