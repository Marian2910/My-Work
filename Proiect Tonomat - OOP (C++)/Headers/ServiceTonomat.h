//
// Created by Marian Mutu on 25.04.2022.
//

#ifndef LAB9_10_SERVICETONOMAT_H
#define LAB9_10_SERVICETONOMAT_H


#include "RepositoryGeneric.h"
#include "Tonomat.h"
#include <vector>
using namespace std;

class ServiceTonomat {

private:
    RepositoryGeneric<Tonomat> &repoTonomat;
public:
    explicit ServiceTonomat(RepositoryGeneric<Tonomat> &repoTonomat);
    ~ServiceTonomat();
    void addProdus(const string& cod, const string& nume, float pret);
    void deleteProdus(const string& cod);
    vector<Tonomat> getAll();
    void updateProdus(const string& cod, const string& numeNou, float pretNou);
    void updateSold(int cincizeci, int zece);
    void addSold(const string& cod, const string& nume, float pret, int cincizeci, int zece);
    int showSold();
    void addToSold(int cincizeci, int zece);
};


#endif //LAB9_10_SERVICETONOMAT_H
