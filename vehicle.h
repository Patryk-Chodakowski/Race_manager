#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsItem>

#include "route_element.h"

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
    double fuelTankCapacity = 50;

    double fuelTankLevel = fuelTankCapacity;
    double mileage = 0.1;

    int currentTrack = 0;
    Point position;
    double angle;

    int width,height;
    int velocity;

    int maxVelocity;
    int acceleration;

    int distance = 0;
    int currlap =-1;
    int step = 0;

    Route_Element *current_element;

    QGraphicsItem *model;

public:
    Vehicle(Color color);

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
    void setFuelTankCapacity(int c);
//    void setFuelTankLevel(int l);

    int get_track();
    bool getOvertaking();
    bool getOvertaken();
    int getDistance();
    int getStep();
    int getLap();
    int getFuelTankCapacity();
    int getFuelTankLevel();

    void drive(int step_time);
    bool turning_to_pitstop();

    Route_Element* get_route_element();
    Point get_position();
    double get_angle();
    void updatePosition();
    int get_velocity();

    QGraphicsItem * get_graphic_item();
};

#endif // VEHICLE_H
