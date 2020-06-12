#include "qgraphicsarcitem.h"

QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent)
    :QGraphicsItem()
{

}

QRectF QGraphicsArcItem::boundingRect() const
{

    return QRectF(0,0,100,100);
}

void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);

    int start = 90 * 16;
    int end = 270 * 16;

    painter->drawArc(rec,start,end);
}

