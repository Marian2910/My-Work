//
// Created by Marian Mutu on 28.04.2022.
//

#include "ServiceUtilizator.h"

ServiceUtilizator::ServiceUtilizator(RepositoryUtilizator &repoUtilizator) : repoUtilizator(repoUtilizator){}

ServiceUtilizator::~ServiceUtilizator() {}


void ServiceUtilizator::addUtilizator(const string &id, const string &nume, const string &prenume) {
    Utilizator utilizator(id, nume, prenume);
    repoUtilizator.addElem(utilizator);
}

void ServiceUtilizator::deleteUtilizator(const string &id) {
    for(int i= 0; i< repoUtilizator.getAll().size(); i++)
        if(repoUtilizator.getAll()[i].getId() == id)
            repoUtilizator.deleteElem(repoUtilizator.getAll()[i]);
}

vector<Utilizator> ServiceUtilizator::getAll() {
    return repoUtilizator.getAll();
}

void ServiceUtilizator::updateUtilizator(const string &id, const string &nume, const string &prenume) {
    Utilizator utilizator(id, nume, prenume);
    for(int i= 0; i< repoUtilizator.getAll().size(); i++)
        if(repoUtilizator.getAll()[i].getId() == id)
            repoUtilizator.updateElem(repoUtilizator.getAll()[i], utilizator);
}

Utilizator ServiceUtilizator::getUtilizatorDupaId(const string &id) {
    for(int i=0; i<repoUtilizator.getAll().size();i++)
        if(repoUtilizator.getAll()[i].getId() == id)
            return repoUtilizator.getAll()[i];
    Utilizator u("err", "", "");
    return u;
}

string ServiceUtilizator::getIdUtilizator(const string &nume, const string &prenume) {
    for(int i=0; i<repoUtilizator.getAll().size();i++)
        if(repoUtilizator.getAll()[i].getNume() == nume && repoUtilizator.getAll()[i].getPrenume() == prenume)
            return repoUtilizator.getAll()[i].getId();

    return "notfound";
}
