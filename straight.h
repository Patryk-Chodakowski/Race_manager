#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "route_element.h"

/*!
    \brief Klasa definiująca prostą trasy
*/

class Straight : public Route_Element
{
public:
    Straight();

    /*!
    \brief Konstruktor klasy
    \param _start Punkt początkowy prostej
    \param _start_radius Promień łuku w punkcie startowym
    \param _end Punkt końcowy prostej
    \param _end_radius Promień łuku w punkcie końcowym
    */
    Straight(Point<int> _start, int start_radius,Point<int> _end,int end_radius);
    ~Straight();

    /*!
    \brief Rzutowanie pozycji (dystansu) pojazdu na element trasy (prosta)
    \param v Rzutowany pojazd
    \return Dystans na rzutowanym elemencie
    */
    int positionToDistanceProjection(Vehicle *v) override;
    /*!
    \brief Ustawienie pojazdu na zadanym dystansie (od pkt początkowego)
    \param v Ustawiany pojazd
    \param length Zadany dystans
    */
    void placeOnLength(Vehicle *v, int length) override;
    /*!
    \brief Zwraca kąt w położeniu początkowym elementu (prostej)
    \return Kąt początkowy
    */
    int get_angle() override;

    /*!
    \brief Przelicza pozycję pojazdu przy ruchu o zadany krok
    \param v Pojazd
    \param step Zadany krok
    \return krok jaki nalezy jeszcze wykonać, jesli przekorczono element (jeśli nie przekroczono zwraca 0)
    */
    int calculateTrajectory(Vehicle* v,int step) override;

    /*!
    \brief Funkcja debugująca, wypisuje najważniejsze parametry utworzonej prostej
    */
    void log_straight();
    /*!
    \brief Funkcja debugująca, wypisuje najważniejsze parametry utworzonej prostej
    */
    void log() override;

};

#endif // STRAIGHT_H
