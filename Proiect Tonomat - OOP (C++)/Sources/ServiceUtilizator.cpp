//
// Created by Marian Mutu on 25.04.2022.
//

#include "../Headers/ServiceUtilizator.h"

ServiceUtilizator::ServiceUtilizator(RepositoryGeneric<Utilizator> &repoUtilizator): repoUtilizator(repoUtilizator) {}

ServiceUtilizator::~ServiceUtilizator() = default;

void ServiceUtilizator::addUtilizator(float monede, const string &cod) {
    Utilizator utilizator(monede, cod);
    repoUtilizator.addElem(utilizator);
}

vector<Utilizator> ServiceUtilizator::getAllUtilizator() {
    return this->repoUtilizator.getAll();
}

void ServiceUtilizator::updateUtilizator(const string &cod) {
    for(auto i:  repoUtilizator.getAll())
        if(i.getCod() == cod)
            i.setCod(cod);
}
