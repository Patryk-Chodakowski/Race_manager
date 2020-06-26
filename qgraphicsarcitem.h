#ifndef QGRAPHICSARCITEM_H
#define QGRAPHICSARCITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "point.h"

class QGraphicsArcItem : public QGraphicsItem
{
    QRectF build_rectanlge;
    int quater;
public:
    QGraphicsArcItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent = 0);
    QGraphicsArcItem(Point centre,Point start, Point end, int radius);

    QRectF boundingRect() const;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void changeApperanccene(const QPen &pen = QPen(), const QBrush &brush = QBrush());
};

#endif // QGRAPHICSARCITEM_H
