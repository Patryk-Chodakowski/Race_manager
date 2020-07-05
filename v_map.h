#ifndef V_MAP_H
#define V_MAP_H

#include <trail.h>
#include <QGraphicsScene>
#include <QGraphicsItem>

/*!
    \brief Klasa wizualizująca mapę
*/

class V_Map
{
    ///wskaźnik na trasę
    Trail *way;

public:
    /*!
    \brief Konstruktor trasy
    \param *trail Wskaźnik na trasę
    */
    V_Map(Trail *trail);
    ~V_Map();

    /*!
    \brief Funkcja rysująca trasę na scenie
    \param *scene Wskaźnik na scenę
    */
    void draw_map(QGraphicsScene *scene);
    /*!
    \brief Funkcja rysująca pojazd na scenie
    \param *scene Wskaźnik na scenę
    \param *vehicle Wskaźnik na pojazd
    */
    void draw_vehicle(QGraphicsScene *scene,Vehicle *vehicle);
    /*!
    \brief Funkcja usuwająca pojazd ze sceny
    \param *scene Wskaźnik na scenę
    \param *vehicle Wskaźnik na pojazd
    */
    void removeVehicleFromScene(QGraphicsScene *scene,Vehicle *vehicle);
};

#endif // V_MAP_H
