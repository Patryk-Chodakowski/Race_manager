#ifndef QGRAPHICSARCITEM_H
#define QGRAPHICSARCITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "point.h"

class QGraphicsArcItem : public QGraphicsItem
{
    QRectF build_rectanlge;
    int quater;
    int width;

    const int x;
    const int y;
    const int r;
public:
    QGraphicsArcItem(Point centre,Point start, Point end, int radius, int width);

    QRectF boundingRect() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

#endif // QGRAPHICSARCITEM_H
