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
//    QGraphicsArcItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent = 0);
    QGraphicsArcItem(Point centre,Point start, Point end, int radius, int width);

    QRectF boundingRect() const override;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape() const override;
//    void changeApperanccene(const QPen &pen = QPen(), const QBrush &brush = QBrush());

};

#endif // QGRAPHICSARCITEM_H
