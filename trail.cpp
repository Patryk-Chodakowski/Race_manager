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
    //prosta tworzona z aktualnego i nastepnego
    //luk na aktualnym, z poprzedniego i nastepnego
    int size = source.size();
    int current, next, prev, pitStart, pitEnd;
    length = 0;

    current = finish_line;
    next = current + 1;
    prev = current - 1;

    if (next > size - 1) next = 0;
    if (prev < 0) prev = size - 1;

    Straight *begin = new Straight(source[current].p,source[current].r,source[next].p,source[next].r);
    length += begin->get_length();
    begin->set_finish_line();

    begin->log_straight();

    current++;
    if (current > size - 1) current = 0;
    next = current + 1;
    prev = current - 1;
    if (next > size - 1) next = 0;
    if (prev < 0) prev = size - 1;

    trail_elements = begin;
    Route_Element *list_end = begin;
    Route_Element *pit_entry, *pit_exit;

    for (int i = 0 ; i < size - 1 ; i++){
        cout << i << endl;

        Curve *arc = new Curve(source[prev].p,source[current].p,source[next].p,source[current].r);

        arc->log_curve();

        Straight *line = new Straight(source[current].p,source[current].r,source[next].p,source[next].r);

        line->log_straight();

        if (source[prev].type != 'P' && source[current].type == 'P' && source[next].type == 'P'){
            list_end->set_turn_to_pitlane();
            list_end->set_pitlane_element(arc);
            pit_entry = list_end;
            pitStart = current;
        };

        if (source[prev].type == 'P' && source[current].type == 'P' && source[next].type != 'P'){
            arc->set_pitlane();
            arc->set_pit_end();
            pitEnd = current;
            line->set_pitlane_element(arc);
            pit_exit = arc;
        };

        if (source[current].type == 'P' && source[next].type == 'P'){
            arc->set_pitlane();
            line->set_pitlane();            
        };

        if (!arc->get_pitlane()) length += arc->get_length();
        if (!line->get_pitlane()) length += line->get_length();

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
    cout << "ostatnia prosta"<< endl;
    Straight *line = new Straight(source[pitStart].p, - source[pitStart].r,source[pitEnd].p, - source[pitEnd].r);
    length += line->get_length();

    line->log_straight();
    cout << "trasa: " << length << endl;

    pit_entry->set_next(line);
    line->set_prev(pit_entry);
    line->set_next(pit_exit);
    pit_exit->set_prev(line);

    list_end->set_next(begin);
    begin->set_prev(list_end);
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
