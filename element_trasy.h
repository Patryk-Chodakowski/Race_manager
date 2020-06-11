#ifndef ELEMENT_TRASY_H
#define ELEMENT_TRASY_H
#include "punkt.h"

class Element_trasy
{
    Punkt poczatek, koniec;
    Element_trasy *nastepny, *poprzedni;
public:
    Element_trasy();
    void wyznacz_droge();
};

#endif // ELEMENT_TRASY_H
