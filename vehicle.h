#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsItem>
//#include <QObject>

#include "route_element.h"
#include "team.h"

class Route_Element;

/*!
\brief  Typ wyliczeniowy określający dozwolone kolory graczy
*/
enum class Color {YELLOW,BLACK,GREEN,RED};
///\brief Zwraca angielską nazwę koloru
QString getColorName(Color color);

class Vehicle
{
protected:
    ///czy skręca na pitstop
    bool goToPitstop = false;
    ///czy wyprzedza
    bool is_overtaking = false;
    ///czy jest wyprzedzany
    bool is_overtaken = false;
    ///czy jedzie
    bool running = true;

    ///bazowa pojemność zbiornika paliwa
    double baseTankCapacity = 200;
    ///szerokość pojazdu
    int width = 40;
    ///długość pojazdu
    int height = 60;
    ///prędkość bazowa pojazdu
    int baseVelocity = 5;
    ///prędkość maksymalna pojazdu
    int maxVelocity = baseVelocity;
    ///przyspieszenie pojazdu
    int acceleration = 1;

    ///poziom ulepszenia zbiornika
    int tankLevel = 0;
    ///poziom napełnienia zbiornika
    double fuelTankLevel = 0;
    ///spalanie paliwa
    double mileage = 0.1;
    ///aktualny tor jazdy
    int currentTrack = 0;
    ///pozycja pojazdu
    Point<int> position;
    ///kąt obrotu pojazdu
    double angle = 0;
    ///prędkość pojazdu
    int velocity = 0;
    ///styl jazdy
    int rideStyle = 0;
    ///pokonana odległość
    int distance = 0;
    ///aktualne okrążenie
    int currlap =-1;
    ///aktualny krok
    int step = 0;

    ///wskaźnik na element trasy na którym jest pojazd
    Route_Element *current_element = nullptr;
    ///wskaźnik na obiekt graficzny odpowiadający pojazdowi
    QGraphicsItem *model = nullptr;

public:
    /*!
    \brief Konstruktor klasy
    \param color Kolor pojazdu
    */
    Vehicle(Color color);
    /*!
    \brief Konstruktor klasy
    \param color Kolor pojazdu
    \param fuelTankUpgrade poziom ulepszenia zbiornika paliwa
    \param *team wskaźnik na zespół inźynierów
    */
    Vehicle(Color color,int fuelTankUpgrade, Team *team = new Team());
    ~Vehicle();

    ///\brief Ustawia czy pojazd ma zjechać na pitstop
    void setGoToPitStop(bool go);
    ///\brief Zmienia stan na przeciwny (ruch/stop)
    void toggleRun();
    ///\brief Przelicza krok do wykonania przez pojazd
    void calculateStep();
    ///\brief Zatrzymuje samochód
    void stopVehicle();

    ///\brief Ustawia pozycję pojazdu
    void set_position(Point<int> _position);
    ///\brief Ustawia kąt obrotu pojazdu
    void set_angle(double value);
    ///\brief Ustawia wskaźnik aktualnego elementu trasy
    void set_route_element(Route_Element *element);
    ///\brief Ustawia tor jazdy pojazdu
    void set_track(int track);

    ///\brief Ustawia czy pojazd wyprzedza
    void setOvertaking(bool a);
    ///\brief Ustawia czy pojazd jest wyprzedzany
    void setOvertaken(bool a);
    ///\brief Ustawia przejechany przez pojazd dystans
    void setDistance(int d);
    ///\brief Ustawia krok pojazdu
    void setStep(int s);
    ///\brief Zwiększa liczbę okrążeń o 1
    void incraseLap();
    ///\brief Ustawia styl jazdy pojazdu. 1 - przyspieszony, 0 - normalny, -1 - spowolniony
    void setRideStyle(int style);
    ///\brief Ustawia maksymalną prędkość pojazdu
    void setMaxVelocity(int v);

    ///\brief Zwraca aktualny tor jazdy
    int get_track();
    ///\brief Zwraca czy pojazd wyprzedza
    bool getOvertaking();
    ///\brief Zwraca czy pojazd jest wyprzedzany
    bool getOvertaken();
    ///\brief Zwraca przejechany dystans
    int getDistance();
    ///\brief Zwraca krok pojazdu
    int getStep();
    ///\brief Zwraca liczbę przejechanych okrążeń
    int getLap();
    ///\brief Ustawia liczbę przejechanych okrążeń
    void setLap(int lap);
    ///\brief Zwraca pojemność baku paliwa
    int getFuelTankCapacity();
    ///\brief Zwraca poziom paliwa
    int getFuelTankLevel();
    ///\brief Zwraca styl jazdy
    int getRideStyle();
    ///\brief Zwraca prędkość pojazdu
    int get_velocity();
    ///\brief Zwraca maksymalną prędkość
    int getMaxVelocity();
    ///\brief Zwraca uleprzenie baku paliwa
    int getTankUpgrage();

    ///\brief Wylicza położenie pojazdu na podstawie kroku (wykonuje ruch)
    void drive();
    ///\brief Zwraca czy pojazd skręca na pitstop
    bool turning_to_pitstop();

    ///\brief Ulepsza pojazd zadanym zespołem inżynierów. Wpływa na maksymalną prędkość
    void upgradeVehicle(Team *team);
    ///\brief Ulepsza zbiornik paliwa zadanym poziomem
    void upgradeTank(int level);
    ///\brief Zeruje chwilowe parametry pojazdu przed kolejnym startem
    void resetVehicleBeforeStart();

    ///\brief Zwraca wskaźnik na element trasy na którym jest pojazd
    Route_Element* get_route_element();
    ///\brief Zwraca pozycję pojazdu
    Point<int> get_position();
    ///\brief Zwraca kąt obrotu pojazdu
    double get_angle();
    ///\brief Aktualizuje pozycję pojazdu (modelu graficznego)
    void updatePosition();

    ///\brief Zwraca wskaźnik na obiekt graficzny odpowiadający pojazdowi
    QGraphicsItem * get_graphic_item();
};

#endif // VEHICLE_H
