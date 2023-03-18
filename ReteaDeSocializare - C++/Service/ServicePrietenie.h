//
// Created by Marian Mutu on 28.04.2022.
//

#ifndef RETEADESOCIALIZARE_SERVICEPRIETENIE_H
#define RETEADESOCIALIZARE_SERVICEPRIETENIE_H

#include "../Repository/RepositoryPrietenie.h"
#include "../Domain//Prietenie.h"

class ServicePrietenie {
private:
    RepositoryPrietenie repoPrietenie;
public:
    explicit ServicePrietenie(RepositoryPrietenie &repoPrietenie);
    ~ServicePrietenie();
    void addPrietenie(const string& id1, const string& id2);
    void deletePrietenie(const string& id1, const string &id2);
    void deleteAllPrietenie(const string& id);
    Array<Prietenie> getAll();
    bool prietenieExistenta(const string& id1, const string& id2);
};


#endif //RETEADESOCIALIZARE_SERVICEPRIETENIE_H
