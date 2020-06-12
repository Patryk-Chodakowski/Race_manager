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
        int x,y,r;
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
                point.x = stoi(tab[1]);
                point.y = stoi(tab[2]);
            }
            if (tab[0] == "P" || tab[0] == "F"){
                point.type = tab[0].at(0);
                point.x = stoi(tab[1]);
                point.y = stoi(tab[2]);
                point.r = stoi(tab[3]);
            }else{
                point.type = '0';
                point.x = stoi(tab[0]);
                point.y = stoi(tab[1]);
                point.r = stoi(tab[2]);
            }
            source.push_back(move(point));
        }
        i++;
    }

    //tworzenie elementow trasy
    int size = source.size();






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
