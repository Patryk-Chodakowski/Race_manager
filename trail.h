#ifndef TRAIL_H
#define TRAIL_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "straight.h"
#include "curve.h"

using namespace std;

/*!
\brief Klasa trasy wyścigu
*/

class Trail
{
    ///szerokość trasy
    int width= 0;
    ///nazwa trasy
    string name = "GP Monaco";
    ///odstęp bocznych torów od środkowego
    int interspace = 20;
    ///długość trasy
    int length = 0;
    ///liczba okrążeń trasy
    int laps = 6;

    ///wskaźnik na piewszy element trasy (wskaźnik na listę dwukierunkową)
    Route_Element *central_trail;

public:
    /*!
    \brief Konstruktor Klasy
    \param ścieżka do pliku mapy
    */
    Trail(string sourceFile = "punkty_mapy.txt");
    ~Trail();

    /*!
    \brief Tworzy listę elementów trasy
    \param sourceFile ścieżka do pliku z mapą
    */
    void create_elements(string sourceFile);
    ///\brief Ustawia liczbę okrążeń trasy
    void setLaps(int l);
    ///\brief Ustawia nazwę trasy
    void setName(string n);

    ///\brief Zwraca długość trasy
    int getLength();
    ///\brief Zwraca liczbę okrążeń
    int getLaps();
    ///\brief Zwraca nazwę trasy
    string getName();
    ///\brief Zwraca pierwszy element trasy
    Route_Element *get_elements();

private:
    /*!
    \brief Funkcja rozbijająca sting wg wskazanego znaku
    \param s Tekst źródłowy
    \param delim Znak rozdzielający dane
    */
    vector<string> explode(string const & s, char delim);
};

#endif // TRAIL_H
