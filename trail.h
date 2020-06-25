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
    int width;
    string name;\
    int interspace = 20;
    int length;

    Route_Element *inner_trail, *outer_trail;
    Route_Element *central_trail;

public:
    Trail();
    void create_elements();
    Route_Element *get_elements();

private:
    vector<string> explode(string const & s, char delim);
};

#endif // TRAIL_H
