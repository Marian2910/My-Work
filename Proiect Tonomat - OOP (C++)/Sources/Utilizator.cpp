//
// Created by Marian Mutu on 16.04.2022.
//

#include "../Headers/Utilizator.h"

Utilizator::Utilizator() {
    this->monede = 0;
    this->cod = "";
}

Utilizator::Utilizator(float monede, const string &cod) {
    this->monede = monede;
    this->cod = cod;
}

Utilizator::~Utilizator() {}

float Utilizator::getMonede() {
    return this->monede;
}

string Utilizator::getCod() {
    return this->cod;
}

void Utilizator::setCod(const string &cod) {
    this->cod = cod;
}

ostream &operator<<(ostream &os, const Utilizator &t) {
    os << " ";
    os << t.monede << " ";
    os << t.cod<<"\n";
    return os;
}

istream &operator>>(istream &is, Utilizator &t) {
    float monede;
    string cod;
    is>>monede;
    is>>cod;
    t.monede = monede;
    t.cod = cod;
    return is;
}

