#ifndef ROUTE_ELEMENT_H
#define ROUTE_ELEMENT_H

#include <QGraphicsItem>

#include "qgraphicsarcitem.h"
#include "vehicle.h"
#include "point.h"

class Vehicle;

/*!
\brief Klasa elementu trasy
*/

class Route_Element
{
protected:
    ///Szerokość trasy
    int width = 80;
    ///kierunek elementu
    Point<int> direction;
    ///Punkt poczatkowy i końcowy
    Point<int> start, end;
    ///Długość elementu
    int length;
    ///Odstęp bocznych tras od głównej
    int interspace = 0;
    ///Dległość całej trasy do aktualnego elementu
    int lengthSoFar = 0;

    ///Wskażnik na kolejny element
    Route_Element *next = nullptr;
    ///Wskażnik na poprzedni element
    Route_Element *prev = nullptr;
    ///Wskażnik na zjazd na pitstop
    Route_Element *pitlane_element = nullptr;

    ///Ograniczenie prędkości na pitlane
    int pit_speed_limit = 3;
    ///czy to wewnętrzny łuk
    bool is_inner = false;
    ///czy to pitlane
    bool is_pitlane = false;
    ///czy ma skręt na pitlane
    bool is_turn_to_pitlane = false;
    ///czy jest początkiem pitlane
    bool pit_start = false;
    ///czy jest końcem pitlane
    bool pit_end = false;
    ///czy jest linią mety
    bool is_finish_line = false;
    ///czy jest krzywą
    bool curve = false;

    ///Element graficzny opowiadający temu elementowi
    QGraphicsItem *item;

public:
    /*!
    \brief Ustawia punkt początkowy
    */
    void set_start(Point<int> point);
    /*!
    \brief Ustawia punkt końcowy
    */
    void set_end(Point<int> point);
    /*!
    \brief Ustawia kierunek elementu na postawie punktu początkowego i końcowego
    */
    void set_direction(Point<int> _start, Point<int> _end);

    /*!
    \brief Ustawia kolejny element
    \param *element Wskaźnik na następny element
    */
    void set_next(Route_Element *element);
    /*!
    \brief Ustawia poprzedni element
    \param *element Wskaźnik na poprzedni element
    */
    void set_prev(Route_Element *element);
    /*!
    \brief Ustawia skręt na pitlane
    \param *element Wskaźnik na skręt na pitlane
    */
    void set_pitlane_element(Route_Element *element);

    /*!
    \brief Ustawia element na element wewnętrzny
    */
    void set_inner();
    /*!
    \brief Ustawia element na pitlane
    */
    void set_pitlane();
    /*!
    \brief Ustawia element na skręt do pitlane
    */
    void set_turn_to_pitlane();
    /*!
    \brief Ustawia element na start pitlane
    */
    void set_pit_start();
    /*!
    \brief Ustawia element na koniec pitlane
    */
    void set_pit_end();
    /*!
    \brief Ustawia element na metę
    */
    void set_finish_line();
    /*!
    \brief Ustawia odstęp bocznych tras od środkowej
    */
    void set_interspace(int space);
    /*!
    \brief Ustawia długość trasy do bierzącego elementu
    */
    void setLengthSoFar(int l);

    /*!
    \brief Zwraca odstęp bocznych tras od środkowej
    */
    int get_interspace();
    /*!
    \brief Zwraca ograniczenie prędkości elementu
    */
    int getSpeedLimit();
    /*!
    \brief Zwraca czy element jest pitlane
    */
    bool get_pitlane();
    /*!
    \brief Zwraca czy element jest skrętem do pitlane
    */
    bool get_turn_to_pitlane();
    /*!
    \brief Zwraca czy element jest początkiem pitlane
    */
    bool get_pit_start();
    /*!
    \brief Zwraca czy element jest końcem pitlane
    */
    bool get_pit_end();
    /*!
    \brief Zwraca czy element jest metą
    */
    bool get_finish_line();
    /*!
    \brief Zwraca czy element jest wewnętrzym elementem (łuk wewnętrzny)
    */
    bool get_inner();
    /*!
    \brief Zwraca czy element jest łukiem
    */
    bool is_curve();
    /*!
    \brief Zwraca szerokość elementu
    */
    int getWidth();

    /*!
    \brief Zwraca długość elementu
    */
    int get_length();
    /*!
    \brief Zwraca długość trasy do bierzącego elementu
    */
    int getLengthSoFar();

    /*!
    \brief Zwraca wskaźnik na następny element
    */
    Route_Element* get_next_element();
    /*!
    \brief Zwraca wskaźnik na poprzedni element
    */
    Route_Element* get_prev_element();
    /*!
    \brief Zwraca wskaźnik na skręt do pitlane
    */
    Route_Element* get_pitlane_element();
    /*!
    \brief Zwraca wskaźnik na objazd pitlane
    */
    Route_Element* getPitBypass();

    /*!
    \brief Zwraca kierunek elementu
    */
    Point<int> get_dir();
    /*!
    \brief Zwraca punkt początkowy elementu
    */
    Point<int> get_start();
    /*!
    \brief Zwraca punkt końcowy elementu
    */
    Point<int> get_end();

    /*!
    \brief Zwraca dystans odpowiadający dystansowi przebytemu przez rzut na objazd pitlane
    \param *v Wskaźnik na rzutowany pojazd
    */
    virtual int positionToDistanceProjection(Vehicle *v);

    /*!
    \brief Funkcja ustawiająca pojazd na zadanej odległości na aktualnym elemencie
    \param *v Przemieszczany pojazd
    \param _length Odległość
    */
    virtual void placeOnLength(Vehicle *v, int _length);


    /*!
    \brief Zwraca kąt w położeniu początkowym elementu (łuku)
    \return Kąt początkowy
    */
    virtual int get_angle();

    /*!
    \brief Przelicza pozycję pojazdu przy ruchu o zadany krok
    \param v Pojazd
    \param step Zadany krok
    \return krok jaki nalezy jeszcze wykonać, jesli przekorczono element (jeśli nie przekroczono zwraca 0)
    */
    virtual int calculateTrajectory(Vehicle* v,int step);

    /*!
    \brief Funkcja debugująca, wypisuje najważniejsze parametry utworzonego łuku
    */
    virtual void log();

    Route_Element();
    virtual ~Route_Element();

    ///\brief Zwraca wskaźnik na obiekt graficzny odpowiadający elementowi
    QGraphicsItem* get_graphic_item();

};



#endif // ROUTE_ELEMENT_H
