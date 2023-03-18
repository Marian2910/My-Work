//
// Created by Marian Mutu on 16.04.2022.
//

#ifndef LAB9_10_PRODUSE_H
#define LAB9_10_PRODUSE_H

#include <iostream>
#include <ostream>
#include <istream>
using namespace std;

class Produse {
private:
    string cod;
    string nume;
    float pret;
public:
    Produse();
    Produse(const string& cod, const string& nume, float pret);
    ~Produse();
    string getCod();
    string getNume();
    float getPret();
    void setCod(string cod);
    void setNume(string nume);
    void setPret(float pret);
    Produse &operator=(const Produse& t);
    friend ostream& operator<<(ostream& os, const Produse& t);
    friend istream& operator>>(istream& is, Produse& t);
    bool operator==(const Produse &t);
};


#endif //LAB9_10_PRODUSE_H
