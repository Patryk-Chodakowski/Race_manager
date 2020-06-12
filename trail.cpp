#include "trail.h"

Trail::Trail()
{

}

void Trail::create_elements(){
    fstream file;
    string tmp;
    vector<string> tab;

    file.open("punkty_mapy.txt",ios::in);
    if(!file.good()){
        cout << "Nie udalo sie wczytac pliku z mapa" << endl;
        file.close();
        return;
    }

    while(!file.eof()){
        getline(file,tmp);
        tab = explode(tmp,',');

        if (tmp != ""){
            for (string el : tab){
                cout << el << " ";
            }
        cout << endl;
        }



    }

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
