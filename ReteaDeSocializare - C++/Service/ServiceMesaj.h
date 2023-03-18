//
// Created by Marian Mutu on 28.04.2022.
//

#ifndef RETEADESOCIALIZARE_SERVICEMESAJ_H
#define RETEADESOCIALIZARE_SERVICEMESAJ_H

#include "../Repository/RepositoryMesaj.h"
#include "../Domain//Mesaj.h"

class ServiceMesaj {
private:
    RepositoryMesaj repoMesaj;
public:
    explicit ServiceMesaj(RepositoryMesaj &repositoryMesaj);
    ~ServiceMesaj();
    void addMesaj(const string& id1, const string& id2, const string &mesaj);
    void deleteMesaj(const string& id);
    Array<Mesaj> getAll();
    vector<pair<string, string>> getConversatie(const string& id1, const string& id2);
};


#endif //RETEADESOCIALIZARE_SERVICEMESAJ_H
