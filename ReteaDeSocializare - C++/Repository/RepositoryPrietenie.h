//
// Created by Marian Mutu on 16.05.2022.
//

#ifndef RETEADESOCIALIZARE_REPOSITORYPRIETENIE_H
#define RETEADESOCIALIZARE_REPOSITORYPRIETENIE_H
#include "TADArray.h"
#include "../Domain/Prietenie.h"

#include <iostream>
#include <fstream>
using namespace std;

class RepositoryPrietenie {
private:
    Array<Prietenie> prietenii;
    string filename;
public:
    explicit RepositoryPrietenie(const string& filename);
    RepositoryPrietenie();
    void addPrietenie(const Prietenie& utilizator);
    Array<Prietenie> getAll();
    void deletePrietenie(const Prietenie& utilizator);

private:
    void saveToFile();
    void loadFromFile();

};



#endif //RETEADESOCIALIZARE_REPOSITORYPRIETENIE_H
