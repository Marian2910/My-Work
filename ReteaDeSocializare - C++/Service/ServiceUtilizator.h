//
// Created by Marian Mutu on 28.04.2022.
//

#ifndef RETEADESOCIALIZARE_SERVICEUTILIZATOR_H
#define RETEADESOCIALIZARE_SERVICEUTILIZATOR_H


#include "../Domain/Utilizator.h"
#include "../Repository//RepositoryUtilizator.h"
#include <vector>
using namespace std;

class ServiceUtilizator {

private:
    RepositoryUtilizator &repoUtilizator;
public:
    explicit ServiceUtilizator(RepositoryUtilizator &repoUtilizator);
    ~ServiceUtilizator();
    void addUtilizator(const string& id, const string& nume,  const string& prenume);
    void deleteUtilizator(const string& id);
    vector<Utilizator> getAll();
    void updateUtilizator(const string& id, const string& nume, const string& prenume);
    Utilizator getUtilizatorDupaId(const string &id);
    string getIdUtilizator(const string &nume, const string &prenume);
};


#endif //RETEADESOCIALIZARE_SERVICEUTILIZATOR_H
