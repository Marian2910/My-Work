//
// Created by Marian Mutu on 25.04.2022.
//

#include "../Headers/Tonomat.h"

Tonomat::Tonomat():Produse() {}

Tonomat::Tonomat(const string &cod, const string &nume, float pret, const Monede &sold): Produse(cod, nume, pret) {
    this->sold = sold;
}

Tonomat::~Tonomat() {}

int Tonomat::getSold() {
    return 50 * sold.getCinzeciBani() + 10 * sold.getZeceBani();
}

void Tonomat::setSold(Monede sold) {
    this->sold = sold;
}

Tonomat::Tonomat(const string &cod, const string &nume, float pret) : Produse(cod, nume, pret) {}

Monede Tonomat::getMonede() {
    return sold;
}
