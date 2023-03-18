//
// Created by Marian Mutu on 28.04.2022.
//

#ifndef RETEADESOCIALIZARE_RETEA_H
#define RETEADESOCIALIZARE_RETEA_H
#include "..//Repository/TADArray.h"
#include "..//Domain/Utilizator.h"
#include "..//Service//ServiceUtilizator.h"
#include "..//Service//ServicePrietenie.h"
#include "..//Service//ServiceMesaj.h"

class Retea {
private:
    ServiceUtilizator& serviceutilizator;
    ServicePrietenie& serviceprietenie;
    ServiceMesaj& servicemesaj;
public:
    Retea(ServiceUtilizator& serviceutilizator, ServicePrietenie& serviceprietenie, ServiceMesaj& servicemesaj);
    ~Retea();
    void runMenu();
private:
    static void displayMenu();
    static void displayMenuUtilizator();
    void uiaddUtilizator();
    void uishowUtilizatori();
    void uideleteUtilizator(const string &id);
    void uiupdateUtilizator(const string &id);
    void uiaddPrietenie(const string &id);
    void uideletePrietenie(const string &id);
    void uishowPrietenie(const string &id);
    void uihandlemessages(const string &id);
    void uihandleConectare();
    void runMeniuUtilizator(const string &id);
    void uisearch();
    void handleContulMeu(const string &id);
    static void displayMenuContulMeu();

    void uiaddMesaj(const string &ide, const string& idd);

    void uihandleConversation(const string &basicString, const string& basicString1);
};


#endif //RETEADESOCIALIZARE_RETEA_H
