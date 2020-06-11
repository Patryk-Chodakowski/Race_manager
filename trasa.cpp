#include "trasa.h"

Trasa::Trasa()
{

}

Trasa::Punkt_mapy* Trasa::wczytaj_punkty_trasy(){
    Punkt_mapy *punkt;
    fstream plik;
    string dane;
    vector<string> tab;

    plik.open("punkty_mapy.txt",ios::in);
    if(!plik.good()){
        cout << "Nie udalo sie wczytac pliku z mapa" << endl;
        plik.close();
        return 0;
    }

    while(!plik.eof()){
        getline(plik,dane);
        tab = explode(dane,',');

        if ( tab[0] != "P"){

        }else{

        }

    }


    plik.close();
    return 0;
}

void Trasa::tworz_elementy(){
    Punkt_mapy* punkt;
    punkt = wczytaj_punkty_trasy();
}

vector<string> Trasa::explode(string const & s, char delim){
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }
    return result;
}
