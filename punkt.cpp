#include "punkt.h"

Punkt::Punkt(int _x, int _y)
{
    x = _x;
    y = _y;
}
int Punkt::get_x(){
    return x;
}
int Punkt::get_y(){
    return y;
}
void Punkt::set_x(int a){
    x = a;
}
void Punkt::set_y(int a){
    y = a;
}
