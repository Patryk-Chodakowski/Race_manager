#ifndef PUNKT_H
#define PUNKT_H


class Punkt
{
    int x,y;
public:
    Punkt(int _x = 0, int _y = 0);
    int get_x();
    int get_y();
    void set_x(int a);
    void set_y(int a);
};

#endif // PUNKT_H
