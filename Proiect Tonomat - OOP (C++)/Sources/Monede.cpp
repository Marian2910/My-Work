//
// Created by Marian Mutu on 25.04.2022.
//

#include "../Headers/Monede.h"

Monede::Monede() {
    this->cinzeciBani = 0;
    this->zeceBani = 0;
}

Monede::Monede(int cinzeciBani, int zeceBani) {
    this->cinzeciBani = cinzeciBani;
    this->zeceBani = zeceBani;
}

Monede::~Monede() {}

int Monede::getCinzeciBani() const {
    return this->cinzeciBani;
}

int Monede::getZeceBani() const {
    return this->zeceBani;
}

void Monede::setCinzeciBani(int cinzeciBani) {
    this->cinzeciBani = cinzeciBani;
}

void Monede::setZeceBani(int zeceBani) {
    this->zeceBani = zeceBani;
}

Monede &Monede::operator=(const Monede &monede) {
    setCinzeciBani(monede.cinzeciBani);
    setZeceBani(monede.zeceBani);
    return *this;
}

bool Monede::operator==(const Monede &m) {
    return (this->cinzeciBani == m.cinzeciBani && this->zeceBani == m.zeceBani);
}


