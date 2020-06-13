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
    double width;
    string name;
    Route_Element *trail_elements;

public:
    Trail();
    void create_elements();
    Route_Element *get_elements();

private:
    vector<string> explode(string const & s, char delim);
};

#endif // TRAIL_H
