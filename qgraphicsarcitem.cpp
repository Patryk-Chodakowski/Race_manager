#include "qgraphicsarcitem.h"

//QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent)
//    :QGraphicsItem()
//{
//    QRectF rec(x,y,radius,radius);
//    build_rectanlge = rec;
//    quater = 0;
//    width = 1;
//}

QGraphicsArcItem::QGraphicsArcItem(Point centre, Point start, Point end, int radius, int _width)
    :QGraphicsItem(), x(centre.get_x() - radius), y(centre.get_y() - radius), r(radius)
{

    //rysowanie luku ze sprawdzeniem strony
    width = _width;
    quater = ArcQuaterFromPoint(start,centre,end);
    setFlag(ItemStacksBehindParent);

//    Point dir = prev.direction_vector(current);
//    Point s(current.get_x()-dir.get_x()*radius,current.get_y()-dir.get_y()*radius);
//    this->set_start(s);

//    dir = current.direction_vector(next);
//    Point e(current.get_x()+dir.get_x()*radius,current.get_y()+dir.get_y()*radius);
//    this->set_end(e);


    QRectF rec = QRectF(x,y,2*radius,2*radius);
    build_rectanlge = rec;
}

QRectF QGraphicsArcItem::boundingRect() const
{
    return QRectF(x,y,2*r,2*r);
}

void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();


//    QBrush brush(Qt::gray);

    int start_angle = 0;
    if (quater != 0){
        start_angle = (quater-1) * 90 * 16;
    }
    int end_angle = 90 * 16;

    painter->setPen(QPen(Qt::gray,width,Qt::SolidLine,Qt::FlatCap,Qt::RoundJoin));
    painter->drawArc(rec,start_angle,end_angle);
}

QPainterPath QGraphicsArcItem::shape() const
{

}

//void QGraphicsArcItem::changeApperanccene(const QPen &pen, const QBrush &brush)
//{

//}

