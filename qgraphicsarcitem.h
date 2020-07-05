#ifndef QGRAPHICSARCITEM_H
#define QGRAPHICSARCITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "point.h"

/*!
\brief Klasa wizualizująca łuk trasy
*/

class QGraphicsArcItem : public QGraphicsItem
{
    ///prostokąt opakowujący łuk
    QRectF build_rectanlge;
    ///ćwiartka układu współrzędych
    int quater;
    ///szerokość łuku
    int width;

    ///współrzędna x prostokąta opakowującego
    const int x;
    ///współrzędna y prostokąta opakowującego
    const int y;
    ///promien łuku
    const int r;
public:
    /*!
    \brief Konstruktor klasy
    \param centre Punkt środkowy łuku
    \param start Punkt początkowy łuku
    \param end Punkt końcowy łuku
    \param radius Promień łuku
    \param width Szerokość łuku
    */
    QGraphicsArcItem(Point<int> centre,Point<int> start, Point<int> end, int radius, int width);

    ///\brief Zwraca prostokąt opakowujący łuk
    QRectF boundingRect() const override;

    /*!
    \brief Funkcja rysująca łuk
    */
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

#endif // QGRAPHICSARCITEM_H
