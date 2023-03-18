//
// Created by Marian Mutu on 17.04.2022.
//

#ifndef RETEADESOCIALIZARE_MESAJ_H
#define RETEADESOCIALIZARE_MESAJ_H


#include <istream>
#include <ostream>
#include <iostream>
using namespace std;

class Mesaj {
private:
    string idEmitator;
    string idDestinatar;
    string mesaj;
public:
    Mesaj();
    Mesaj(const string & idEmitator, const string &idDestinatar,const string &mesaj);
    ~Mesaj();
    string getEmitator();
    string getDestinatar();
    string getMesaj();
    void setEmitator(string ide);
    void setDestinatar(string idd);
    void setMesaj(string mesaj);
    Mesaj &operator=(const Mesaj& m);
    bool operator==(const Mesaj& m);
    friend ostream& operator<<(ostream& os, const Mesaj& m);
    friend istream& operator>>(istream& is, Mesaj& m);


};


#endif //RETEADESOCIALIZARE_MESAJ_H
