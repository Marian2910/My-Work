//
// Created by Marian Mutu on 28.04.2022.
//

#ifndef RETEADESOCIALIZARE_REPOSITORYGENERIC_H
#define RETEADESOCIALIZARE_REPOSITORYGENERIC_H

#include "TADMultime.h"
#include "../Domain/Utilizator.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class RepositoryUtilizator {
private:
    MultimeOrdonata<Utilizator> utilizatori;
    string filename;
public:
    explicit RepositoryUtilizator(const string& filename);
    RepositoryUtilizator();
    void addElem(const Utilizator& entity);
    vector<Utilizator> getAll();
    void deleteElem(Utilizator entity);
    void updateElem(Utilizator oldEntity, const Utilizator& newEntity);
    void saveToFile();
    void loadFromFile();

};

#endif //RETEADESOCIALIZARE_REPOSITORYGENERIC_H