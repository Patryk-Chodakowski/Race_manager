#ifndef QGRAPHICSARCITEM_H
#define QGRAPHICSARCITEM_H
#include <QGraphicsItem>
#include <QPainter>

class QGraphicsArcItem : public QGraphicsItem
{
public:
    QGraphicsArcItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void changeApperanccene(const QPen &pen = QPen(), const QBrush &brush = QBrush());
};

#endif // QGRAPHICSARCITEM_H
