//
// Created by Marian Mutu on 17.04.2022.
//

#ifndef RETEADESOCIALIZARE_PRIETENIE_H
#define RETEADESOCIALIZARE_PRIETENIE_H


#include "Utilizator.h"
#include <iostream>
#include <string>
#include <ostream>
#include <istream>
using namespace std;

class Prietenie {
private:
    string idu1;
    string idu2;
public:
    Prietenie();
    Prietenie(const string &u1, const string &u2);
    string getId1();
    string getId2();
    void setId1(const string &id);
    void setId2(const string &id);
    ~Prietenie();
    Prietenie &operator=(const Prietenie& u);
    bool operator==(const Prietenie& u);
    friend ostream& operator<<(ostream& os, const Prietenie& p);
    friend istream& operator>>(istream& is, Prietenie& p);
};


#endif //RETEADESOCIALIZARE_PRIETENIE_H
