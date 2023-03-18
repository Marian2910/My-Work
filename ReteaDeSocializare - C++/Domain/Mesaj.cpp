//
// Created by Marian Mutu on 17.04.2022.
//

#include "Mesaj.h"

#include <utility>
#include <iomanip>

string Mesaj::getEmitator() {
    return idEmitator;
}

string Mesaj::getDestinatar() {
    return idDestinatar;
}
string Mesaj::getMesaj(){
    return this->mesaj;
}

void Mesaj::setEmitator(string ide){
    this->idEmitator = std::move(ide);
}
void Mesaj::setDestinatar(string idd){
    this->idDestinatar = std::move(idd);
}

void Mesaj::setMesaj(string mesajNou) {
    this->mesaj = mesajNou;
}

Mesaj &Mesaj::operator=(const Mesaj &m) {
    setEmitator(m.idEmitator);
    setDestinatar(m.idDestinatar);
    setMesaj(m.mesaj);
    return *this;
}

bool Mesaj::operator==(const Mesaj &m) {
    return (idEmitator == m.idEmitator && idDestinatar == m.idDestinatar && mesaj == m.mesaj);
}

ostream &operator<<(ostream &os, const Mesaj &m) {
     os<<m.idEmitator<<" ";
     os<<m.idDestinatar<<" ";
     os<<std::quoted(m.mesaj)<<" ";
    return os;
}

istream &operator>>(istream &is, Mesaj &m) {
    is>>m.idEmitator;
    is>>m.idDestinatar;
    is>>std::quoted(m.mesaj);
    return is;
}

Mesaj::Mesaj(const string &idEmitator, const string &idDestinatar,const string &mesaj) {
    this->idEmitator = idEmitator;
    this->idDestinatar = idDestinatar;
    this->mesaj = mesaj;
}

Mesaj::Mesaj() {
}

Mesaj::~Mesaj() = default;
