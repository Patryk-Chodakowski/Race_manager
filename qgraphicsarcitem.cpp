#include "qgraphicsarcitem.h"

QGraphicsArcItem::QGraphicsArcItem(Point<int> centre, Point<int> start, Point<int> end, int radius, int _width)
    :QGraphicsItem(), x(centre.get_x() - radius), y(centre.get_y() - radius), r(radius)
{
    //rysowanie luku ze sprawdzeniem strony
    width = _width;
    quater = ArcQuaterFromPoint(start,centre,end);
    setFlag(ItemStacksBehindParent);

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

    int start_angle = 0;
    if (quater != 0){
        start_angle = (quater-1) * 90 * 16;
    }
    int end_angle = 90 * 16;

    painter->setPen(QPen(Qt::gray,width,Qt::SolidLine,Qt::FlatCap,Qt::RoundJoin));
    painter->drawArc(rec,start_angle,end_angle);
}
