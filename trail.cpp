#include "trail.h"

Trail::Trail()
{
    trail_elements = new Route_Element();
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
                point.r = 0;
            }
            else{
                if (tab[0] == "P"){
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
            }
            source.push_back(move(point));
        }
        i++;
    }

    file.close();

    //tworzenie elementow trasy
    int size = source.size();
    int current, next, prev;

    current = finish_line;
    next = current + 1;
    prev = current - 1;

    if (next > size - 1) next = 0;
    if (prev < 0) prev = size - 1;

    Straight *begin = new Straight(source[current].p,source[current].r,source[next].p,source[next].r);
    begin->log_straight();

    current++;
    if (current > size - 1) current = 0;
    next = current + 1;
    prev = current - 1;
    if (next > size - 1) next = 0;
    if (prev < 0) prev = size - 1;

    trail_elements = begin;
    Route_Element *list_end = begin;

    for (int i = 0 ; i < size - 1 ; i++){
        cout << i << endl;

        Curve *arc = new Curve(source[prev].p,source[current].p,source[next].p,source[current].r);
        arc->log_curve();

        Straight *line = new Straight(source[current].p,source[current].r,source[next].p,source[next].r);
        line->log_straight();

        list_end->set_next(arc);
        arc->set_prev(list_end);
        arc->set_next(line);
        line->set_prev(arc);
        list_end = line;

        current++;
        if (current > size - 1) current = 0;
        next = current + 1;
        prev = current - 1;
        if (next > size - 1) next = 0;
        if (prev < 0) prev = size - 1;
    }
}

Route_Element *Trail::get_elements()
{
    return trail_elements;
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
