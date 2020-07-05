#ifndef SIMULATION_H
#define SIMULATION_H

#include <QTimer>
#include <QObject>
#include <iomanip>

#include "trail.h"
#include "v_map.h"
#include "player.h"

/*!
\brief Klasa symulacji wyścigu
*/

class Simulation : public QObject
{
    Q_OBJECT;

    ///wskaźnik na trasę wyścigu
    Trail *road;
    ///wskaźnik na zegar symulacji
    QTimer *timer;

    ///wskaźnik na wektor graczy
    vector<Player*> *pv;
    ///wskaźnik na gracza sterowanego
    Player *human;

    ///aktualne okrążenie
    int currentLap = 0;
    ///minimalny odstęp między pojazdami
    int minDistance = 80;
    ///czas próbkowania zegara
    int sample_time = 20;

public:
    /*!
    \brief Konstruktor klasy
    \param players Wektor uczestników wyścigu
    \param sourceFile Ścieżka do pliku mapy
    */
    Simulation(vector<Player*>& players,string sourceFile);
    ~Simulation();

    ///\brief Zwraca wskaźnik na trasę wyścigu
    Trail *get_trail();
    ///\brief Zwraca wskaźnik na sterowanego gracza
    Player *get_human();
    ///\brief Zwraca wskaźnik na wektor graczy
    vector<Player*> *getPlayers();

    ///\brief Ustawia pojazdy na starcie
    void setVehiclesOnStart();

    ///\brief Sprawdza odległości między pojazdami i zarządza ich ruchem
    void checkPositionBetweenVehicles();
    ///\brief Sprawdza pozycję uczestników wyścigu
    void checkPlayersPlace();

    ///\brief Uruchamia/wznawia zegar symulacji
    void simStart();
    ///\brief Zatrzymuje zegar symulacji
    void simPause();

    ///\brief Kończy wyścig i rozdaje nagrody
    void raceEnd();
    ///\brief Zwraca aktualne okrążenie
    int getCurrentLap();

public: signals:
    ///\brief Sygnał odświeżenia widoku
    void updateView();
    ///\brief Sygnał zamknięcia okna symulacji
    void closeSimWindow();

    ///\brief Sygnał zablokowania przycisku pitstopu
    void disablePitButton();
    ///\brief Sygnał aktywowania przycisku pitstopu
    void enablePitButton();

    ///\brief Sygnał zakończenia wyścigu
    void raceEnded();

public slots:
    ///\brief Slot wykonania ruchu pojazdów w wyścigu
    void makeMoves();
};

#endif // SIMULATION_H
