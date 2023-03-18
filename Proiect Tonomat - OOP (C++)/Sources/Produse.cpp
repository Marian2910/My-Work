//
// Created by Marian Mutu on 16.04.2022.
//

#include "../Headers/Produse.h"

#include <utility>

Produse::Produse() {
    this->cod = "";
    this->nume = "";
    this->pret = 0;
}

Produse::Produse(const string& cod, const string& nume, float pret) {
    this->cod = cod;
    this->nume = nume;
    this->pret = pret;
}

Produse::~Produse() {}

string Produse::getCod() {
    return this->cod;
}

string Produse::getNume() {
    return this->nume;
}

float Produse::getPret() {
    return this->pret;
}

void Produse::setCod(string cod) {
    this->cod = move(cod);
}

void Produse::setNume(string nume) {
    this->nume = move(nume);
}

void Produse::setPret(float pret) {
    this->pret = pret;
}

Produse &Produse::operator=(const Produse &t) {
    this->setCod(t.cod);
    this->setNume(t.nume);
    this->setPret(t.pret);
    return *this;
}

bool Produse::operator==(const Produse &t) {
    return (this->cod == t.cod && this->nume == t.nume && this->pret == t.pret);
}

ostream &operator<<(ostream &os, const Produse &t) {
    os << t.cod << " ";
    os << t.nume<<" ";
    os << t.pret <<"\n";
    return os;
}

istream &operator>>(istream &is, Produse &t) {
    string cod, nume;
    float pret;
    is>>cod;
    is>>nume;
    is>>pret;
    t.cod = cod;
    t.nume = nume;
    t.pret = pret;
    return is;
}
