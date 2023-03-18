//
// Created by Marian Mutu on 17.04.2022.
//

#ifndef RETEADESOCIALIZARE_UTILIZATOR_H
#define RETEADESOCIALIZARE_UTILIZATOR_H


#include "Prietenie.h"
#include <iostream>
#include <ostream>
#include <istream>
#include "../Repository/TADArray.h"
using namespace std;

class Utilizator {
private:
    string id;
    string nume;
    string prenume;
public:
    Utilizator();
    Utilizator(const string &id, const string &nume, const string &prenume);
    ~Utilizator();
    string getId();
    string getNume();
    string getPrenume();
    void setId(const string &idd);
    void setNume(const string &n);
    void setPrenume(const string &p);
    Utilizator &operator=(const Utilizator& u);
    bool operator==(const Utilizator& u);
    friend ostream& operator<<(ostream& os, const Utilizator& u);
    friend istream& operator>>(istream& is, Utilizator& u);
    bool operator<(const Utilizator& u);
    bool operator>(const Utilizator& u);

};


#endif //RETEADESOCIALIZARE_UTILIZATOR_H
