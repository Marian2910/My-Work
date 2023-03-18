//
// Created by Marian Mutu on 20.05.2022.
//

#include "RepositoryMesaj.h"


RepositoryMesaj::RepositoryMesaj(const string &filename) {
    if(!filename.empty())
        this->filename = filename;
    loadFromFile();
}

RepositoryMesaj::RepositoryMesaj() {
    this->filename = "";
}


void RepositoryMesaj::addMesaj(const Mesaj& mesaj) {
    this->mesaje.push_back(mesaj);
    this->saveToFile();
}

Array<Mesaj> RepositoryMesaj::getAll() {
    return this->mesaje;
}

void RepositoryMesaj::deleteMesaj(const Mesaj &mesaj) {
    for(int i = 0; i < mesaje.size(); i++)
        if(mesaje.getElem(i) == mesaj)
            mesaje.deleteElem(i);
    this->saveToFile();
}

void RepositoryMesaj::saveToFile()
{
    if (!filename.empty())
    {
        ofstream fo(this->filename);
        for (int i = 0; i < this->mesaje.size();i++)
        {
            fo << this->mesaje.getElem(i) << endl;
        }
        fo.close();

    }
    else
        return;
}

void RepositoryMesaj::loadFromFile()
{
    Mesaj mesaj;
    if (!this->filename.empty())
    {
        ifstream fi(this->filename);
        while (fi>>mesaj)
        {
            this->addMesaj(mesaj);
        }
        fi.close();
    }
}

