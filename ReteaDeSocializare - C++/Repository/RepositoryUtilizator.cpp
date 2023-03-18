//
// Created by Marian Mutu on 20.05.2022.
//

#include "RepositoryUtilizator.h"
using namespace std;

RepositoryUtilizator::RepositoryUtilizator(const string &filename) {
    if(!filename.empty())
        this->filename = filename;
    loadFromFile();
}

RepositoryUtilizator::RepositoryUtilizator() {
    this->filename = "";
}

void RepositoryUtilizator::addElem(const Utilizator& utilizator) {
    utilizatori.adauga(utilizator);
    this->saveToFile();
}

vector<Utilizator> RepositoryUtilizator::getAll() {
    return this->utilizatori.get_lista_ordonata();
}

void RepositoryUtilizator::deleteElem(Utilizator entity) {
    vector<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    for (auto & i : lista) {
        if (i.getId() == entity.getId()) {
            this->utilizatori.sterge(i);
        }
    }
    this->saveToFile();
}

void RepositoryUtilizator::updateElem(Utilizator oldEntity, const Utilizator &newEntity) {
    vector<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    for (auto & i : lista) {
        if (i.getId() == oldEntity.getId()) {
            this->utilizatori.sterge(i);
            this->utilizatori.adauga(newEntity);
        }
    }
    this->saveToFile();
}

void RepositoryUtilizator::saveToFile()
{
    if (!filename.empty())
    {
        ofstream fo(this->filename);
        vector<Utilizator> lista = this->utilizatori.get_lista_ordonata();
        for (auto & i : lista) {
            fo << i << endl;
        }
        fo.close();
    }
    else
        return;
}

void RepositoryUtilizator::loadFromFile()
{
    Utilizator utilizator;
    if (!this->filename.empty())
    {
        ifstream fi(this->filename);
        while (fi>>utilizator)
        {
            this->utilizatori.adauga(utilizator);
        }
        fi.close();
    }
}

