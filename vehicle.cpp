#include "vehicle.h"

Vehicle::Vehicle(Color color)
{
    resetVehicleBeforeStart();

    QString txt = getColorName(color);

    QString path(txt + "_car");
    QPixmap item(path);
    item = item.scaled(width,height,Qt::KeepAspectRatio);
    model = new QGraphicsPixmapItem(item);
    model->setTransformOriginPoint(model->boundingRect().center());
}

Vehicle::Vehicle(Color color, int fuelTankUpgrade, Team *team)
    :Vehicle(color)
{
    upgradeVehicle(team);
    upgradeTank(fuelTankUpgrade);

    fuelTankLevel = getFuelTankCapacity();
}

Vehicle::~Vehicle()
{
    delete model;
}

void Vehicle::setGoToPitStop(bool go)
{
    goToPitstop = go;
}

void Vehicle::toggleRun()
{
    if(running) running = false;
    else running = true;
}

void Vehicle::calculateStep()
{
    int currentSpeedLimit = maxVelocity;

    if (!running){
       step = 0;
       return;
    }

    //wyznacz predkosc
    if(current_element->get_pitlane() && !current_element->get_pit_start() && !current_element->get_pit_end()){
        if (velocity > current_element->getSpeedLimit()) velocity--;
        else velocity++;

        //uzupelnienie paliwa
        fuelTankLevel = getFuelTankCapacity();
        if (goToPitstop){
            goToPitstop = false;
        }
    }
    else{
        velocity += acceleration;

        currentSpeedLimit += rideStyle;

        //zuzycie paliwa
        fuelTankLevel = fuelTankLevel - mileage - 0.05*rideStyle;
        if (fuelTankLevel <= 0){
            fuelTankLevel = 0;
            currentSpeedLimit = 3;
        }
    }

    if (velocity > currentSpeedLimit) velocity = currentSpeedLimit;
    if (velocity < 0) velocity = 0;


    //wyznacz skok
    step = velocity;
}

void Vehicle::stopVehicle()
{
    step = 0;
    velocity = 0;
}

void Vehicle::set_position(Point<int> _position)
{
    position = _position;
}

void Vehicle::set_angle(double value)
{
    angle = value;
}

void Vehicle::set_route_element(Route_Element *element)
{
    current_element = element;
}

void Vehicle::set_track(int track)
{
    currentTrack = track;
}

void Vehicle::setOvertaken(bool a)
{
    is_overtaken = a;
}

void Vehicle::setOvertaking(bool a)
{
    is_overtaking = a;
}

void Vehicle::setDistance(int d)
{
    distance = d;
}

void Vehicle::setStep(int s)
{
    step = s;
}

void Vehicle::incraseLap()
{
    currlap++;
}

void Vehicle::setRideStyle(int style)
{
    if (style > 1) rideStyle = 1;
    else if (style < -1) rideStyle = -1;
    else rideStyle = style;
}

void Vehicle::setMaxVelocity(int v)
{
    maxVelocity = v;
}

int Vehicle::get_track()
{
    return currentTrack;
}

bool Vehicle::getOvertaken()
{
    return is_overtaken;
}

bool Vehicle::getOvertaking()
{
    return is_overtaking;
}

int Vehicle::getDistance()
{
    return distance;
}

int Vehicle::getStep()
{
    return step;
}

int Vehicle::getLap()
{
    return currlap;
}

void Vehicle::setLap(int lap)
{
    currlap = lap;
}

int Vehicle::getFuelTankCapacity()
{
    int current = baseTankCapacity;
    switch (tankLevel) {
    case 1:
        current = baseTankCapacity*1.5;
        break;
    case 2:
        current = baseTankCapacity*2;
        break;
    default:
        break;
    }

    return current;
}

int Vehicle::getFuelTankLevel()
{
    return fuelTankLevel;
}

int Vehicle::getRideStyle()
{
    return rideStyle;
}

int Vehicle::getTankUpgrage()
{
    return tankLevel;
}

Route_Element *Vehicle::get_route_element()
{
    return current_element;
}

Point<int> Vehicle::get_position()
{
    return position;
}

double Vehicle::get_angle()
{
    return angle;
}

void Vehicle::updatePosition()
{
    model->setX(position.get_x() - width/2);
    model->setY(position.get_y() - height/2);
    model->setRotation(angle);
}

int Vehicle::get_velocity()
{
    return velocity;
}

int Vehicle::getMaxVelocity()
{
    return maxVelocity;
}

QGraphicsItem *Vehicle::get_graphic_item()
{
    return model;
}

void Vehicle::drive()
{
    step = current_element->calculateTrajectory(this,step);
    while (step != 0){

        if(goToPitstop && current_element->get_turn_to_pitlane()){
            current_element = current_element->get_pitlane_element();
        }else{
            current_element = current_element->get_next_element();
        }

        step = current_element->calculateTrajectory(this,step);
    };

    updatePosition();
}

bool Vehicle::turning_to_pitstop()
{
    return goToPitstop;
}

void Vehicle::upgradeVehicle(Team *team)
{
    maxVelocity = baseVelocity + team->getEngineers();
}

void Vehicle::upgradeTank(int level)
{
    if (level > 0 && level < 3)
        tankLevel = level;
}

void Vehicle::resetVehicleBeforeStart()
{
    goToPitstop = false;
    running = true;
    fuelTankLevel = getFuelTankCapacity();
    velocity = 0;
    rideStyle = 0;
    distance = 0;
    currlap = -1;
    step = 0;
    angle = 0;
    maxVelocity = baseVelocity;
}

QString getColorName(Color color)
{
    QString txt;
    switch (int(color)) {
    case 0:
        txt = "yellow";
        break;
    case 1:
        txt = "black";
        break;
    case 2:
        txt = "green";
        break;
    case 3:
        txt = "red";
        break;
    default:
        txt = "black";
        break;
    }
    return txt;
}
