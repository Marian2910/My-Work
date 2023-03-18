//
// Created by Marian Mutu on 16.05.2022.
//

#ifndef RETEADESOCIALIZARE_REPOSITORYMESAJ_H
#define RETEADESOCIALIZARE_REPOSITORYMESAJ_H

#include "TADArray.h"
#include "../Domain/Mesaj.h"

#include <iostream>
#include <fstream>
using namespace std;

class RepositoryMesaj {
private:
    Array<Mesaj> mesaje;
    string filename;
public:
    explicit RepositoryMesaj(const string& filename);
    RepositoryMesaj();
    void addMesaj(const Mesaj& mesaj);
    Array<Mesaj> getAll();
    void deleteMesaj(const Mesaj& mesaj);

private:
    void saveToFile();
    void loadFromFile();

};


#endif //RETEADESOCIALIZARE_REPOSITORYMESAJ_H
