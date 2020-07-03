#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsItem>
//#include <QObject>

#include "route_element.h"
#include "team.h"

class Route_Element;

enum class Color {YELLOW,BLACK,GREEN,RED};

QString getColorName(Color color);

class Vehicle
{
protected:
    bool goToPitstop = false;
    bool is_overtaking = false;
    bool is_overtaken = false;
    bool running = true;

//    double fuelTankCapacity = 400;
    double baseTankCapacity = 200;
//    double fuelTankCapacity = baseTankCapacity;

    int tankLevel = 0;
    double fuelTankLevel = 0;
    double mileage = 0.1;

    int currentTrack = 0;
    Point position;
    double angle;

    int width,height;
    int velocity;

    int baseVelocity = 5;
    int maxVelocity = baseVelocity;
    int acceleration;

    int rideStyle = 0;
    int distance = 0;
    int currlap =-1;
    int step = 0;

    Route_Element *current_element;

    QGraphicsItem *model;

public:
    Vehicle(Color color);
    Vehicle(Color color,int fuelTankUpgrade, Team *team = new Team());

    void setGoToPitStop(bool go);
    void toggleRun();
    void calculateStep();
    void stopVehicle();

    void set_position(Point _position);
    void set_angle(double value);
    void set_route_element(Route_Element *element);
    void set_track(int track);

    void setOvertaking(bool a);
    void setOvertaken(bool a);
    void setDistance(int d);
    void setStep(int s);
    void incraseLap();
    void setRideStyle(int style);
//    void setFuelTankCapacity(int c);
//    void setFuelTankLevel(int l);

    int get_track();
    bool getOvertaking();
    bool getOvertaken();
    int getDistance();
    int getStep();
    int getLap();
    int getFuelTankCapacity();
    int getFuelTankLevel();
    int getRideStyle();
    int get_velocity();
    int getMaxVelocity();
    int getTankUpgrage();

    void drive(int step_time);
    bool turning_to_pitstop();

    void upgradeVehicle(Team *team);
    void upgradeTank(int level);

    Route_Element* get_route_element();
    Point get_position();
    double get_angle();
    void updatePosition();


    QGraphicsItem * get_graphic_item();

};

#endif // VEHICLE_H
