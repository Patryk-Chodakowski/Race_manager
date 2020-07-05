#ifndef POINT_H
#define POINT_H

#include <iostream>

template<typename T = int>
class Point
{
    ///współrzędne punktu
    T x,y;
public:
    ///\brief Ustawia współrzędną x punktu
    void set_x(T _x){ x = _x;};
    ///\brief Ustawia współrzędną y punktu
    void set_y(T _y){y = _y;};
    ///\brief Zwraca współrzędną x punktu
    T get_x(){return x;};
    ///\brief Zwraca współrzędną y punktu
    T get_y(){return y;};
    /*!
    \brief Zwraca punkt określający kierunek od aktualnego punktu do zadanego punktu punktu
    \param destination Punkt docelowy
    \return Punkt, gdzie współrzędne określają zmianę kierunku od punktu dla którego wywołano funkcję do docelowego będącego parametrem. 1 to zmiana zgodna z kierukiem osi, 0 brak zmiany, -1 przeciwnie do kierunku osi
    */
    Point direction_vector(Point destination){
        T dir_x,dir_y,dx,dy;
        dx = destination.get_x() - x;
        dy = destination.get_y() - y;

        if(dx < 0) dir_x = -1;
        if(dx == 0) dir_x = 0;
        if(dx > 0) dir_x = 1;

        if(dy < 0) dir_y = -1;
        if(dy == 0) dir_y = 0;
        if(dy > 0) dir_y = 1;

        Point result(dir_x,dir_y);
        return result;
    };

    ///\brief Funkcja debugująca, drukuje w konsoli współrzędne punktu
    void log_point(){
        std::cout << "(" << x << "," << y << ")" << std::endl;
    };

    Point(){};

    /*!
    \brief Konstruktor klasy
    \param _x Współrzędna x punktu
    \param _y Współrzędna x punktu
    */
    Point(T _x,T _y){
        x = _x;
        y = _y;
    };
};

/*!
    \brief Zwraca ćwiartkę układu współrzędnych na podstawie punktów charakterystycznych łuku
    \param start Punkt początkowy łuku
    \param centre Punkt startowy łuku
    \param end Punkt końcowy łuku
    \return numer ćwiartki układy kartezjańskiego
*/
int ArcQuaterFromPoint(Point<int> start, Point<int> centre, Point<int> end);

#endif // POINT_H
