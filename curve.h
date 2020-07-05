#ifndef CURVE_H
#define CURVE_H

#include <cmath>

#include "route_element.h"

/*!
    \brief Klasa definiująca łuk trasy
*/


class Curve : public Route_Element
{
    /// promień łuku
    int radius;
    /// ćwiartka układu kartezjańskiego
    int quater;
    ///środek łuku
    Point<int> centre;

public:
    /*!
    \brief Ustawienie promienia łuku
    \param r Promień
    */
    void set_radius(int r);

    /*!
    \brief Utworzenie łuku z zadadnych punktów i promienia
    \param prev Poprzedni punkt trasy
    \param current Aktualny punkt trasy, na którym utworzony zostanie łuk
    \param next Następny punk trasy
    \param _radius Promień łuku
    */
    void set_ends_from_points(Point<int> prev, Point<int> current, Point<int> next, int _radius);

    /*!
    \brief Funkcja debugująca, wypisuje najważniejsze parametry utworzonego łuku
    */
    void log_curve();

    /*!
    \brief Konstruktor klasy tworzący łuk z punktów trasy i promienia
    \param prev Poprzedni punkt trasy
    \param current Aktualny punkt trasy, na którym utworzony zostanie łuk
    \param next Następny punk trasy
    \param _radius Promień łuku
    */
    Curve(Point<int> prev, Point<int> current, Point<int> next, int _radius);
    ~Curve();

    /*!
    \brief Rzutowanie pozycji (dystansu) pojazdu na element trasy (łuk)
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
    \brief Zwraca kąt w położeniu początkowym elementu (łuku)
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
    \brief Funkcja debugująca, wypisuje najważniejsze parametry utworzonego łuku
    */
    void log() override;
};

#endif // CURVE_H
