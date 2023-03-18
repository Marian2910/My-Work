//
// Created by Marian Mutu on 28.04.2022.
//

#include "ServicePrietenie.h"

ServicePrietenie::ServicePrietenie(RepositoryPrietenie &repoPrietenie) : repoPrietenie(repoPrietenie){}

ServicePrietenie::~ServicePrietenie() = default;

void ServicePrietenie::addPrietenie(const string &id1, const string &id2) {
    Prietenie prietenie(id1, id2);
    repoPrietenie.addPrietenie(prietenie);
}

void ServicePrietenie::deletePrietenie(const string &id1, const string &id2) {
    for (int i = 0; i < repoPrietenie.getAll().size(); i++) {
        if (repoPrietenie.getAll().getElem(i).getId1() == id1 && repoPrietenie.getAll().getElem(i).getId2() == id2)
            repoPrietenie.deletePrietenie(repoPrietenie.getAll().getElem(i));
        if (repoPrietenie.getAll().getElem(i).getId1() == id2 && repoPrietenie.getAll().getElem(i).getId2() == id1)
            repoPrietenie.deletePrietenie(repoPrietenie.getAll().getElem(i));
    }
}

Array<Prietenie> ServicePrietenie::getAll() {
    return repoPrietenie.getAll();
}

bool ServicePrietenie::prietenieExistenta(const string &id1, const string &id2) {
    for(int i = 0; i<repoPrietenie.getAll().size(); i++) {
        if (repoPrietenie.getAll().getElem(i).getId1() == id1 && repoPrietenie.getAll().getElem(i).getId2() == id2)
            return true;
        if (repoPrietenie.getAll().getElem(i).getId1() == id2 && repoPrietenie.getAll().getElem(i).getId2() == id1)
            return true;
    }
    return false;
}

void ServicePrietenie::deleteAllPrietenie(const string &id) {
    for (int i = 0; i < repoPrietenie.getAll().size(); i++) {
        if (repoPrietenie.getAll().getElem(i).getId1() == id || repoPrietenie.getAll().getElem(i).getId2() == id)
            repoPrietenie.deletePrietenie(repoPrietenie.getAll().getElem(i));
        }
}

