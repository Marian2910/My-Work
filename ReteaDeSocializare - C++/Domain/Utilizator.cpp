//
// Created by Marian Mutu on 17.04.2022.
//

#include "Utilizator.h"

Utilizator::Utilizator() = default;

Utilizator::Utilizator(const string &id, const string &nume, const string &prenume) {
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
}

//Utilizator::Utilizator(const string &id, const string &nume, const string &prenume, const Array<Utilizator, 30>& listaPrieteni) {
//    this->id = id;
//    this->nume = nume;
//    this->prenume = prenume;
//    this->listaPrieteni.copyArray(listaPrieteni, 30);
//}

Utilizator::~Utilizator() = default;

string Utilizator::getId() {
    return this->id;
}

string Utilizator::getNume() {
    return this->nume;
}

string Utilizator::getPrenume() {
    return this->prenume;
}

void Utilizator::setId(const string &idd) {
    this->id = idd;
}


void Utilizator::setNume(const string &n) {
    this->nume = n;
}

void Utilizator::setPrenume(const string &p) {
    this->prenume = p;
}

Utilizator &Utilizator::operator=(const Utilizator &u) {
    setId(u.id);
    setNume(u.nume);
    setPrenume(u.prenume);
    return *this;
}

bool Utilizator::operator==(const Utilizator &u) {
    return (this->id == u.id && this->nume == u.nume && this->prenume == u.prenume);
}

ostream &operator<<(ostream &os, const Utilizator &u) {
    os<<u.id<<" ";
    os<<u.nume<<" ";
    os<<u.prenume<<"\n";
    return os;
}

istream &operator>>(istream &is, Utilizator &u) {
    is>>u.id;
    is>>u.nume;
    is>>u.prenume;
    return is;
}

bool Utilizator::operator<(const Utilizator &u) {
    return this->id < u.id ;

}

bool Utilizator::operator>(const Utilizator &u) {
    return this->id > u.id;
}

