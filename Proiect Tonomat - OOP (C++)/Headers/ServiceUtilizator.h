//
// Created by Marian Mutu on 25.04.2022.
//

#ifndef LAB9_10_SERVICEUTILIZATOR_H
#define LAB9_10_SERVICEUTILIZATOR_H
#include "RepositoryGeneric.h"
#include "Utilizator.h"

class ServiceUtilizator {
private:
    RepositoryGeneric<Utilizator> &repoUtilizator;
public:
    explicit ServiceUtilizator(RepositoryGeneric<Utilizator> &repoUtilizator);
    ~ServiceUtilizator();
    void addUtilizator(float monede, const string& cod);
    vector<Utilizator> getAllUtilizator();
    void updateUtilizator(const string& cod);
};


#endif //LAB9_10_SERVICEUTILIZATOR_H
