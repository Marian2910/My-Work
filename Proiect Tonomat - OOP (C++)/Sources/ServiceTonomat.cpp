//
// Created by Marian Mutu on 25.04.2022.
//

#include "../Headers/ServiceTonomat.h"

ServiceTonomat::ServiceTonomat(RepositoryGeneric<Tonomat> &repoTonomat): repoTonomat(repoTonomat){}

void ServiceTonomat::addProdus(const string& cod, const string& nume, float pret) {
    Tonomat tonomat(cod, nume, pret);
    this->repoTonomat.addElem(tonomat);
}

void ServiceTonomat::deleteProdus( const string& cod) {
    for(auto i: repoTonomat.getAll())
        if(i.getCod() == cod){
            if(i == repoTonomat.getAll()[0])
                return;
            this->repoTonomat.deleteElem(i);
        }
}

vector<Tonomat> ServiceTonomat::getAll() {
    return this->repoTonomat.getAll();
}

void ServiceTonomat::updateProdus(const string& cod, const string& numeNou, float pretNou) {
    Tonomat produsNou(cod, numeNou, pretNou);
    for(auto i: repoTonomat.getAll())
        if(i.getCod() == cod)
            this->repoTonomat.updateElem(i, produsNou);
}

void ServiceTonomat::updateSold(int cincizeci, int zece) {
    Monede soldNou(cincizeci, zece);
    Tonomat newEntity = repoTonomat.getAll()[0];
    newEntity.setSold(soldNou);
    repoTonomat.updateElem(repoTonomat.getAll()[0], newEntity);
}

void ServiceTonomat::addSold(const string& cod, const string& nume, float pret, int cincizeci, int zece) {
    Monede sold(cincizeci, zece);
    Tonomat tonomat(cod, nume, pret, sold);
    this->repoTonomat.addElem(tonomat);
}

int ServiceTonomat::showSold() {
    return repoTonomat.getAll()[0].getSold();
}


ServiceTonomat::~ServiceTonomat() = default;

void ServiceTonomat::addToSold(int cincizeci, int zece) {
    cincizeci = cincizeci + repoTonomat.getAll()[0].getMonede().getCinzeciBani();
    zece = zece + repoTonomat.getAll()[0].getMonede().getZeceBani();
    Monede soldNou(cincizeci, zece);

    Tonomat newEntity = repoTonomat.getAll()[0];
    newEntity.setSold(soldNou);
    repoTonomat.updateElem(repoTonomat.getAll()[0], newEntity);
}