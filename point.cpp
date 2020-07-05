#include "point.h"

int ArcQuaterFromPoint(Point<int> start, Point<int> centre, Point<int> end)
{
    Point<int> dir_1 = centre.direction_vector(start);
    Point<int> dir_2 = centre.direction_vector(end);

    if (dir_1.get_x() == 1){
        if(dir_2.get_y() == 1){
            return 4;
        }
        if(dir_2.get_y() == -1){
            return 1;
        }
    };

    if(dir_1.get_x() == -1){
        if(dir_2.get_y() == 1){
            return 3;
        }
        if(dir_2.get_y() == -1){
            return 2;
        }
    };

    if(dir_1.get_y() == 1){
        if(dir_2.get_x() == 1){
            return 4;
        }
        if(dir_2.get_x() == -1){
            return 3;
        }
    };

    if(dir_1.get_y() == -1){
        if(dir_2.get_x() == 1){
            return 1;
        }
        if(dir_2.get_x() == -1){
            return 2;
        }
    };
    return 0;
}
