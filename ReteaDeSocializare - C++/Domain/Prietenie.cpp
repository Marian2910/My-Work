//
// Created by Marian Mutu on 17.04.2022.
//

#include "Prietenie.h"

Prietenie::Prietenie() = default;

Prietenie::Prietenie(const string &u1, const string &u2) {
    this->idu1 = u1;
    this->idu2 = u2;
}

string Prietenie::getId1() {
    return this->idu1;
}

string Prietenie::getId2() {
    return this->idu2;
}

void Prietenie::setId1(const string &id){
    this->idu1 = id;
}
void Prietenie::setId2(const string &id){
    this->idu2 = id;
}

Prietenie::~Prietenie() = default;

ostream &operator<<(ostream &os, const Prietenie &u) {
    os<<u.idu1<<" ";
    os<<u.idu2<<" ";
    return os;
}

istream &operator>>(istream &is, Prietenie &u) {
    is>>u.idu1;
    is>>u.idu2;
    return is;
}

Prietenie &Prietenie::operator=(const Prietenie &p) {
    setId1(p.idu1);
    setId2(p.idu2);
    return *this;
}

bool Prietenie::operator==(const Prietenie &p) {
    return (this->idu1 == p.idu1 && this->idu2 == p.idu2);
}
