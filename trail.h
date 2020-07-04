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

class Trail
{
    int width= 0;
    string name = "GP Monaco";
    int interspace = 20;
    int length = 0;
    int laps = 6;

//    Route_Element *inner_trail, *outer_trail;
    Route_Element *central_trail;

public:
    Trail(string sourceFile = "punkty_mapy.txt");
    ~Trail();

    void create_elements(string sourceFile);
    void setLaps(int l);
    void setName(string n);

    int getLength();
    int getLaps();
    string getName();
    Route_Element *get_elements();

private:
    vector<string> explode(string const & s, char delim);
};

#endif // TRAIL_H
