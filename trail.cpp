#include "trail.h"

Trail::Trail()
{

}

void Trail::create_elements(){
    fstream file;
    string tmp;
    vector<string> tab;
    int i = 0, finish_line;

    struct map_source_point{
        Point p;
        int r;
        char type;
    };

    vector<map_source_point> source;

    //wczytanie pliku z mapa
    file.open("punkty_mapy.txt",ios::in);
    if(!file.good()){
        cout << "Nie udalo sie wczytac pliku z mapa" << endl;
        file.close();
        return;
    }

    //wczytanie punktow do budowy mapy z otwartego pliku
    while(!file.eof()){
        map_source_point point;

        getline(file,tmp);
        tab = explode(tmp,',');

        if (tmp != ""){
            if(tab[0] == "F"){
                finish_line = i;
                point.type = tab[0].at(0);
                point.p.set_x(stoi(tab[1]));
                point.p.set_y(stoi(tab[2]));
            }
            if (tab[0] == "P" || tab[0] == "F"){
                point.type = tab[0].at(0);
                point.p.set_x(stoi(tab[1]));
                point.p.set_y(stoi(tab[2]));
                point.r = stoi(tab[3]);
            }else{
                point.type = '0';
                point.p.set_x(stoi(tab[0]));
                point.p.set_y(stoi(tab[1]));
                point.r = stoi(tab[2]);
            }
            source.push_back(move(point));
        }
        i++;
    }

    //tworzenie elementow trasy
    int size = source.size();
    int current, next, prev;

    current = finish_line + 1;
    if (current > size - 1) current = 0;

    next = current + 1;
    prev = current - 1;

    if (next > size - 1) next = 0;
    if (prev < 0) prev = size - 1;

    Point current_point(source[current].p);
    Point prev_point(source[prev].p);
    Point next_point(source[next].p);

    Curve *arc = new Curve();

    prev_point.log_point();
    current_point.log_point();
    next_point.log_point();

    arc->set_direction(current_point,next_point);
    cout << "(" << arc->get_dir().get_x() << "," << arc->get_dir().get_y() << ")" << endl;

    Straight *elem = new Straight();
    Point start(source[current].p);
    Point end(source[next].p);
    elem->set_start(start);
    elem->set_end(end);


    for (size_t i = 0 ; i < size ; i++){

        cout << i << " ";
    }




    cout << source[finish_line].type << endl;

    file.close();
}

vector<string> Trail::explode(string const & s, char delim){
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }
    return result;
}
