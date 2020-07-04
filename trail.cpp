#include "trail.h"

Trail::Trail(string sourceFile)
{
//    central_trail = new Route_Element();
    create_elements(sourceFile);
}

Trail::~Trail()
{
    cout << "USUWAM SCIEZKE" << endl;

    Route_Element *tmp = central_trail->get_next_element();
    while(central_trail->get_next_element()){
        if(central_trail->get_turn_to_pitlane()){
            Route_Element *tmp2 = central_trail->get_pitlane_element();
            Route_Element *tmp3;
            while(tmp2->get_pitlane()){
                tmp3 = tmp2->get_next_element();
                delete tmp2;
                tmp2 = tmp3;
            }
        }
        tmp = central_trail->get_next_element();
        delete central_trail;
        central_trail = tmp;
    }
}

void Trail::create_elements(string sourceFile){
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
//    string sourceFile ="punkty_mapy.txt" ;

    file.open(sourceFile.c_str(),ios::in);
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
                if (tab[0] == "P" || tab[0] == "I"){
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
    //trasa sklada sie z 3 torow
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
    begin->set_interspace(interspace);

//    begin->log_straight();

    current++;
    if (current > size - 1) current = 0;
    next = current + 1;
    prev = current - 1;
    if (next > size - 1) next = 0;
    if (prev < 0) prev = size - 1;

    central_trail = begin;
    Route_Element *list_end = begin;
    Route_Element *pit_entry, *pit_exit;

    for (int i = 0 ; i < size - 1 ; i++){
//        cout << i << endl;

        Curve *arc = new Curve(source[prev].p,source[current].p,source[next].p,source[current].r);
        arc->set_interspace(interspace);

        Straight *line = new Straight(source[current].p,source[current].r,source[next].p,source[next].r);
        line->set_interspace(interspace);

        if(source[current].type == 'I') arc->set_inner();
        if(source[current].type == 'I' && source[next].type == 'I') line->set_inner();

        if (source[prev].type != 'P' && source[current].type == 'P' && source[next].type == 'P'){
            list_end->set_turn_to_pitlane();
            list_end->set_pitlane_element(arc);
            pit_entry = list_end;
            pitStart = current;
            arc->set_pit_start();
        };

        if (source[prev].type == 'P' && source[current].type == 'P' && source[next].type != 'P'){
            arc->set_pitlane();
            arc->set_pit_end();
            pitEnd = current;
            line->set_pitlane_element(arc);
            pit_exit = line;
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

//        arc->log_curve();
//        line->log_straight();

        current++;
        if (current > size - 1) current = 0;
        next = current + 1;
        prev = current - 1;
        if (next > size - 1) next = 0;
        if (prev < 0) prev = size - 1;
    }
    cout << "ostatnia prosta"<< endl;
    Straight *line = new Straight(source[pitStart].p, - source[pitStart].r,source[pitEnd].p, - source[pitEnd].r);
    line->set_interspace(interspace);
    length += line->get_length();

    line->log_straight();
    cout << "trasa: " << length << endl;

    pit_entry->set_next(line);
    line->set_prev(pit_entry);
    line->set_next(pit_exit);
    pit_exit->set_prev(line);

    list_end->set_next(begin);
    begin->set_prev(list_end);

    Route_Element *elem = begin;
    int curr_length = 0;

    do{
//        cout << "curL: " <<  curr_length << " len: " << elem->get_length() << endl;
        if(elem->get_pitlane_element()){
            elem->get_pitlane_element()->setLengthSoFar(curr_length + elem->get_length());
        }
        elem->setLengthSoFar(curr_length);
        curr_length += elem->get_length();
        elem = elem->get_next_element();        
    }while(!elem->get_finish_line());
}

void Trail::setLaps(int l)
{
    laps = l;
}

void Trail::setName(string n)
{
    name = n;
}

int Trail::getLength()
{
    return length;
}

int Trail::getLaps()
{
    return laps;
}

string Trail::getName()
{
    return name;
}

Route_Element *Trail::get_elements()
{
    return central_trail;
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
