#ifndef TRASA_H
#define TRASA_H
#include "w_mapa.h"
#include "element_trasy.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Trasa
{
    double szerokosc;
    W_Mapa mapa;
    Element_trasy *elementy;
    string nazwa;
    struct Punkt_mapy{
        int x,y,r;
        bool is_pit;
        int l;
    };
public:
    Trasa();
    void tworz_elementy();
private:
    Punkt_mapy* wczytaj_punkty_trasy();
    vector<string> explode(string const & s, char delim);
};

#endif // TRASA_H
