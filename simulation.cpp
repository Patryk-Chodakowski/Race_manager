#include "simulation.h"

Simulation::Simulation(vector<Player*>& players,string sourceFile)
{
    pv = &players;

    road = new Trail(sourceFile);
//    road->create_elements();

    human = players.at(0);

//    map = new V_Map(road);
//    map->draw_vehicle();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(makeMoves()));
//    timer->start(sample_time);
}

Trail* Simulation::get_trail()
{
    return road;
}

Player* Simulation::get_human()
{
    return human;
}

vector<Player *> *Simulation::getPlayers()
{
    return pv;
}

//V_Map *Simulation::get_map()
//{
////    return map;
//}

void Simulation::setVehiclesOnStart()
{
      Route_Element *element = road->get_elements()->get_prev_element();

      int distance = 45;
      int to_start = distance;
      int pos = element->get_length() - distance;
      int track = -1;
      int place = 1;

      for(auto& player: (*pv)){
          player->getCar()->set_route_element(element);
          player->getCar()->set_track(track);
          if(track == -1) player->getCar()->setOvertaken(true);
          if(track == 1) player->getCar()->setOvertaking(true);
          element->placeOnLength(player->getCar(),pos);

          player->setPlace(place);
          player->getCar()->setDistance(road->getLength()-to_start);
          to_start += distance;
          pos -= distance;
          track *= (-1);
          place++;
      }
}

void Simulation::checkPositionBetweenVehicles()
{

    int size = pv->size();

    int distance[size][size];
    bool pitstop[size];
    int closestBehind[size];
    int closestAhead[size];

    int closestDistance[size];
    int closestID[size];
    int closestAheadID[size];
    int closestBehindID[size];

    bool canIchangeTrack[size];

    cout << "checking" << endl;

    int opponent = 0;
    int player = 0;

    //różnica odleglosci kazdego auta od kazdego w wyscigu
    //dodatnia gdy jest przed rywalem, ujemna gdy za rywalem
    for (int i=0;i<size;i++){
        //wyzerowanie wspolzaleznosci
        pv->at(i)->getCar()->setOvertaken(false);
        pv->at(i)->getCar()->setOvertaking(false);

        canIchangeTrack[i] = false;
        closestAhead[i] = road->getLength()*road->getLaps();
        closestBehind[i] = - road->getLength()*road->getLaps();

        closestDistance[i] = 2*minDistance;
        closestID[i] = i;

        closestAheadID[i] = i;
        closestBehindID[i] = i;
        pitstop[i] = false;

        //czy jest na pitlane
        if(pv->at(i)->getCar()->get_route_element()->get_pitlane()) pitstop[i] = true;

        //obliczenie odleglosci miedzy autami
        player = pv->at(i)->getCar()->getLap()*road->getLength() + pv->at(i)->getCar()->getDistance();

        for (int j=0;j<size;j++){
            if (i == j){
                distance[i][j] = 0;
                continue;
            }

            opponent = pv->at(j)->getCar()->getLap()*road->getLength() + pv->at(j)->getCar()->getDistance();
            distance[i][j] = opponent - player;

            if (abs(closestDistance[i]) > abs(distance[i][j])){
                closestDistance[i] = distance[i][j];
                closestID[i] = j;
            }

//            if( closestAhead[i] == 0 && distance[i][j] >= 0){
//                closestAhead[i] = distance[i][j];
//                closestAheadID[i] = j;
//            }
//            if(closestBehind[i] == 0 && distance[i][j] < 0){
//                closestBehind[i] = distance[i][j];
//                closestBehindID[i] = j;
//            }

            if(distance[i][j] < closestAhead[i]  && distance[i][j] >= 0){
                closestAhead[i] = distance[i][j];
                closestAheadID[i] = j;
            }
            if(distance[i][j] > closestBehind[i] && distance[i][j] < 0){
                closestBehind[i] = distance[i][j];
                closestBehindID[i] = j;
            }
        }

        if (closestAhead[i] < 0){
            closestAhead[i] = 0;
            closestAheadID[i] = i;
        }
        if (closestBehind[i] > 0){
            closestBehind[i] = 0;
            closestBehindID[i] = i;
        }
    }

    //sprawdzenie warunkow
    for (int i=0;i<size;i++){

        //czy kogos wyprzedzam
        for (int j=0;j<size;j++){
            if (i == j) continue;
//            pitstop[i] == pitstop[j]    // !pitstop[i]
            if (distance[i][j] >= 0 && distance[i][j] < minDistance && pitstop[i] == pitstop[j]){
               pv->at(j)->getCar()->setOvertaken(true);
               pv->at(i)->getCar()->setOvertaking(true);
            }
        }
    }



    for (int i=0;i<size;i++){


        //wjazd na pitstop
        if (pv->at(i)->getCar()->get_route_element()->get_pit_start() && pv->at(i)->getCar()->turning_to_pitstop() && pv->at(i)->getCar()->get_track() == 1){
            for (int j=0;j<size;j++){
                if (i == j) continue;

                if (abs(distance[i][j]) < minDistance){
                    if (!pv->at(j)->getCar()->turning_to_pitstop() && pv->at(j)->getCar()->get_track() == -1){

//                        cout << "Sprawdzam " << pv->at(i)->getCar()->getDistance() << " "<<  pv->at(i)->getCar()->get_route_element()->getLengthSoFar() << endl;

                        if ( pv->at(i)->getCar()->getDistance() < (pv->at(i)->getCar()->get_route_element()->getLengthSoFar() + 10)){
//                            cout << "KOLIZJA" << endl;
                             pv->at(i)->getCar()->stopVehicle();

                        }
                    }


//                    if (!pitstop[j]) pv->at(i)->getCar()->stopVehicle();
//                    else{
//                        if (pitstop[j] && distance[i][j] < (minDistance) &&  distance[i][j] > 0){

//                            if (distance[i][j] < (minDistance - 10)){
//                                pv->at(i)->getCar()->stopVehicle();
//                            }else{
//                                pv->at(i)->getCar()->setStep(pv->at(j)->getCar()->getStep());
//                            }
//                        }
//                    }
                }
            }
        }else

        if (pv->at(i)->getCar()->get_track() == 0){
            if(pv->at(i)->getCar()->getOvertaken() && !pitstop[i]){
                pv->at(i)->getCar()->set_track(-1);
            }
            else{
                if(pv->at(i)->getCar()->getOvertaking()  && !pitstop[i]){
                    if(pv->at(closestAheadID[i])->getCar()->get_track() != 0) pv->at(i)->getCar()->set_track(pv->at(closestAheadID[i])->getCar()->get_track()*(-1));
                    else pv->at(i)->getCar()->set_track(1);
                }
            }
        }
        else{

            //pozycja rozna od 0
            if((pv->at(i)->getCar()->getOvertaking() || pv->at(i)->getCar()->getOvertaken())  && !pitstop[i]){

                //zmiana pasa

                if (pv->at(i)->getCar()->getOvertaking() && pv->at(i)->getCar()->getOvertaken()){
                    if ( pv->at(i)->getCar()->get_track() == pv->at(closestAheadID[i])->getCar()->get_track() &&
                         pv->at(i)->getCar()->get_track() == pv->at(closestBehindID[i])->getCar()->get_track() ){
                         pv->at(i)->getCar()->set_track(pv->at(closestAheadID[i])->getCar()->get_track()*(-1));
                    }
                } else if(pv->at(i)->getCar()->getOvertaking()) {
                    pv->at(i)->getCar()->set_track(pv->at(closestAheadID[i])->getCar()->get_track()*(-1));
                }


                //zachowanie dystansu

                for (int j=0;j<size;j++){
                    if (i == j) continue;

                    if(
                      pv->at(i)->getCar()->get_track() == pv->at(j)->getCar()->get_track() &&
                      pitstop[i] == pitstop[j] &&
                      distance[i][j] < (minDistance) &&  distance[i][j] > 0
                    ){
                        //jesli samochody sa za blisko, i nie moga zmienic pasa, to ten z tylu musi zwolnic
                        if (distance[i][j] < (minDistance - 10)){
                            int step = pv->at(j)->getCar()->getStep() - 1;
                            if (step < 0) step = 0;
                            pv->at(i)->getCar()->setStep(step);
                        }else{
                            pv->at(i)->getCar()->setStep(pv->at(j)->getCar()->getStep());
                        }
                    }

                }

//                if (closestBehind[i] > (-minDistance) && closestBehind[i] < 0){
//                    //wyprzedajacy mnie jest blisko, nie moge zmienic pasa


//                }


//                //zwolnienie jesli jest rywal przed
//                for (int j=0;j<size;j++){
//                    if (i == j) continue;

//                    //jesli sa blisko na tym samym torze
//                    if(
//                        pv->at(i)->getCar()->get_track() == pv->at(j)->getCar()->get_track() &&
//                        pitstop[i] == pitstop[j] &&
//                        distance[i][j] < (minDistance) &&  distance[i][j] > 0
//                      ){
//                        //gdy wyprzedza ale sam nie jest wyprzedzany i jest juz na bocznym torze
//                        if (!pv->at(i)->getCar()->getOvertaken()){
//                            if(pv->at(j)->getCar()->get_track() == 0){
//                                pv->at(i)->getCar()->set_track(1);
//                                pv->at(j)->getCar()->set_track(-1);
//                            }else{
//                                //przyjmuje przeciwna do najblizszego z tylu
//                                pv->at(i)->getCar()->set_track(pv->at(closestID[i])->getCar()->get_track()*(-1));
//                            }
//                        }else{
//                            //jesli samochody sa za blisko, i nie moga zmienic pasa, to ten z tylu musi zwolnic
//                            if (distance[i][j] < (minDistance - 10)){
//                                int step = pv->at(j)->getCar()->getStep() - 1;
//                                if (step < 0) step = 0;
//                                pv->at(i)->getCar()->setStep(step);
//                            }
//                            else{
//                                pv->at(i)->getCar()->setStep(pv->at(j)->getCar()->getStep());
//                            }
//                        }
//                    }
//                }


            } else{
                pv->at(i)->getCar()->set_track(0);
            }
        }

        cout << " Pit " << pv->at(i)->getName() << " ";

        //zwalnianie na pitstopie
        if(pitstop[i]) {
            for (int j=0;j<size;j++){
                if (i == j) continue;
                if (pitstop[j] && distance[i][j] < (minDistance) &&  distance[i][j] > 0){

//                    pv->at(i)->getCar()->setStep(pv->at(j)->getCar()->getStep());


                    if (distance[i][j] < (minDistance - 10)){
//                        int step = pv->at(j)->getCar()->getStep() - 1;
//                        if (step < 0) step = 0;
//                        pv->at(i)->getCar()->setStep(step);

                        pv->at(i)->getCar()->stopVehicle();
                    }else{
                        pv->at(i)->getCar()->setStep(pv->at(j)->getCar()->getStep());
                    }
                }
            }
        }

        //zwalnianie przed wjazdem na pit
        if(pv->at(i)->getCar()->get_route_element()->get_turn_to_pitlane()){
            for (int j=0;j<size;j++){
                if (i == j) continue;
                if(distance[i][j] < (minDistance) &&
                   distance[i][j] > 0 &&
                   pitstop[j] &&
                   pv->at(j)->getCar()->get_track() != 1)
                {
                    if (distance[i][j] < (minDistance - 10)){
                        int step = pv->at(j)->getCar()->getStep() - 1;
                        if (step < 0) step = 0;
                        pv->at(i)->getCar()->setStep(step);
                    }else{
                        pv->at(i)->getCar()->setStep(pv->at(j)->getCar()->getStep());
                    }
                }

            }
        }

        //wyjazd z pitu
        if ((pv->at(i)->getCar()->get_route_element()->get_pit_end() && pv->at(i)->getCar()->get_route_element()->get_pitlane()) ){

            cout << "wyjezdzam ";

                for (int j=0;j<size;j++){
                    if (i == j) continue;
                    if ( abs(distance[i][j]) < minDistance){
                        if (!pitstop[j]) pv->at(i)->getCar()->stopVehicle();
                    }
                }
        }
//        //wjazd na pit

////        cout << pv->at(i)->getCar()->get_route_element()->get_pit_start()

//        if (pv->at(i)->getCar()->get_route_element()->get_pit_start() && pv->at(i)->getCar()->turning_to_pitstop() && pv->at(i)->getCar()->get_track() == 1){
//            cout << "wjezdzam ";

//            for (int j=0;j<size;j++){
//                if (i == j) continue;
//                if ( abs(distance[i][j]) < minDistance){
//                    cout << "STOPP " << i << endl;
//                    pv->at(i)->getCar()->stopVehicle();
//                }
//            }
//        }
        cout << endl;
    }

    for (int i=0;i<size;i++){
        std::cout << "Gracz " << setw(9) << pv->at(i)->getName() << " track: " << setw(2) << pv->at(i)->getCar()->get_track()  << " step: " << pv->at(i)->getCar()->getStep() << ": dist: ";

        for (int j=0;j<size;j++){
            std::cout << setw(5) << distance[i][j] << " ";
        }

        cout << " taken: " << pv->at(i)->getCar()->getOvertaken() << " taking: " << pv->at(i)->getCar()->getOvertaking();
        cout << " lap "<< setw(2) << pv->at(i)->getCar()->getLap() << " distance: " << setw(4) << pv->at(i)->getCar()->getDistance();
        cout << " CAI: " << setw(2) << closestAheadID[i] << " CBI: " << setw(2) << closestBehindID[i] << " CID " << closestID[i] <<  endl;
    }
}

void Simulation::checkPlayersPlace()
{
    int size = pv->size();
    int distance[size];
    bool finish = true;

    int ref = pv->at(0)->getCar()->getLap()*road->getLength() + pv->at(0)->getCar()->getDistance();

    for(int i=0;i<size;i++){
        int opponent = pv->at(i)->getCar()->getLap()*road->getLength() + pv->at(i)->getCar()->getDistance();
        distance[i] = opponent - ref;
        if (pv->at(i)->getCar()->getLap() <= road->getLaps()) finish = false;
    }

    for(int i=0;i<size;i++){
        int tmp = 1;
        for(int j=0;j<size;j++){
            if (distance[i] < distance[j]) tmp++;
        }
        pv->at(i)->setPlace(tmp);
        if(tmp == 1){
            currentLap = pv->at(i)->getCar()->getLap();
            cout << "wstawiam lap" << currentLap <<endl;
        }
    }

    if (finish) raceEnd();

}

void Simulation::simStart()
{
    timer->start(sample_time);
}

void Simulation::simPause()
{
    timer->stop();
}

void Simulation::raceEnd()
{
    cout << "KONIEC WYSCIGU" << endl;

    simPause();

    for (auto& player: (*pv)){
        int points = 0;

        switch (player->getPlace()) {
        case 1:
                points = 25;
            break;
        case 2:
                points = 18;
            break;
        case 3:
                points = 15;
            break;
        case 4:
                points = 12;
            break;
        default:
            break;
        }

        player->setPoints(points);
    }

    //destruktory

    //sygnal wylaczenia, do destruktora


}

int Simulation::getCurrentLap()
{
    return currentLap;
}

void Simulation::makeMoves()
{
    for(auto& player: (*pv)){
        player->getCar()->calculateStep();

        if (!player->isHuman() && player->getCar()->getFuelTankLevel() < player->getCar()->getFuelTankCapacity()*0.2){
            player->getCar()->setGoToPitStop(true);
        }
    }

    checkPositionBetweenVehicles();

    for(auto& player: (*pv)){
        player->getCar()->drive(sample_time);
    }

    if(human->getCar()->get_route_element()->get_pit_start()) disablePitButton();
    if(human->getCar()->get_route_element()->get_pit_end()) enablePitButton();

    checkPlayersPlace();

    updateView();
//    contestants->set_position(Point(contestants->get_position().get_x(),contestants->get_position().get_y() + contestants->get_velocity()));
//    contestants->updatePosition();
}

