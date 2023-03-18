//
// Created by Marian Mutu on 28.04.2022.
//

#include <vector>
#include <tuple>
#include <iomanip>
#include "ServiceMesaj.h"
ServiceMesaj::ServiceMesaj(RepositoryMesaj &repositoryMesaj): repoMesaj(repositoryMesaj) {}

ServiceMesaj::~ServiceMesaj() = default;

void ServiceMesaj::addMesaj(const string &id1, const string &id2, const string &mesaj) {
    Mesaj m(id1, id2, mesaj);
    repoMesaj.addMesaj(m);
}

void ServiceMesaj::deleteMesaj(const string &id) {
    for(int i = 0; i < repoMesaj.getAll().size(); i++)
        if(repoMesaj.getAll().getElem(i).getEmitator() == id || repoMesaj.getAll().getElem(i).getDestinatar() == id)
            repoMesaj.deleteMesaj(repoMesaj.getAll().getElem(i));
}

Array<Mesaj> ServiceMesaj::getAll() {
    return Array<Mesaj>();
}

vector<pair<string, string>> ServiceMesaj::getConversatie(const string &id1, const string &id2) {
    vector<pair<string, string>> conv;
    for(int i = 0; i < repoMesaj.getAll().size(); i++)
        if(repoMesaj.getAll().getElem(i).getEmitator() == id1 && repoMesaj.getAll().getElem(i).getDestinatar() == id2 || repoMesaj.getAll().getElem(i).getEmitator() == id2 && repoMesaj.getAll().getElem(i).getDestinatar() == id1)
            conv.emplace_back(repoMesaj.getAll().getElem(i).getEmitator(), repoMesaj.getAll().getElem(i).getMesaj());
    return conv;
}
