//
// Created by Marian Mutu on 20.05.2022.
//

#include "RepositoryPrietenie.h"

RepositoryPrietenie::RepositoryPrietenie(const string &filename) {
    if(!filename.empty())
        this->filename = filename;
    loadFromFile();
}

RepositoryPrietenie::RepositoryPrietenie() {
    this->filename = "";
}


void RepositoryPrietenie::addPrietenie(const Prietenie& prietenie) {
    this->prietenii.push_back(prietenie);
    this->saveToFile();
}

Array<Prietenie> RepositoryPrietenie::getAll() {
    return this->prietenii;
}

void RepositoryPrietenie::deletePrietenie(const Prietenie &prietenie) {
    for(int i = 0; i < prietenii.size(); i++)
        if(prietenii.getElem(i) == prietenie)
            prietenii.deleteElem(i);
    this->saveToFile();
}

void RepositoryPrietenie::saveToFile()
{
    if (!filename.empty())
    {
        ofstream fo(this->filename);
        for (int i = 0; i < this->prietenii.size();i++)
        {
            fo << this->prietenii.getElem(i) << endl;
        }
        fo.close();

    }
    else
        return;
}

void RepositoryPrietenie::loadFromFile()
{
    Prietenie prietenie;
    if (!this->filename.empty())
    {
        ifstream fi(this->filename);
        while (fi>>prietenie)
        {
            this->addPrietenie(prietenie);
        }
        fi.close();
    }
}