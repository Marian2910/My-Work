//
// Created by Marian Mutu on 16.04.2022.
//

#ifndef LAB9_10_UTILIZATOR_H
#define LAB9_10_UTILIZATOR_H
#include <iostream>
#include <string>
#include <ostream>
#include <istream>
using namespace std;

class Utilizator {
private:
    float monede;
    string cod;
public:
    Utilizator();
    Utilizator(float monede, const string &cod);
    ~Utilizator();
    float getMonede();
    string getCod();
    void setCod(const string &cod);
    friend ostream &operator<<(ostream &os, const Utilizator &t);
    friend istream &operator>>(istream &is, Utilizator &t);
};


#endif //LAB9_10_UTILIZATOR_H
