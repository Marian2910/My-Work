//
// Created by Marian Mutu on 25.04.2022.
//

#ifndef LAB9_10_TONOMAT_H
#define LAB9_10_TONOMAT_H
#include<iostream>
#include <vector>
#include <ostream>
#include "Produse.h"
#include "Monede.h"
using namespace std;

class Tonomat: public Produse {
private:
    Monede sold;
public:
    Tonomat();
    Tonomat(const string& cod, const string& nume, float pret, const Monede& sold);
    Tonomat(const string& cod, const string& nume, float pret);
    ~Tonomat();
    int getSold();
    Monede getMonede();
    void setSold(Monede sold);
};


#endif //LAB9_10_TONOMAT_H
