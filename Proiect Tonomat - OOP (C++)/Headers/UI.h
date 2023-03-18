//
// Created by Marian Mutu on 25.04.2022.
//

#ifndef LAB9_10_UI_H
#define LAB9_10_UI_H
#include "ServiceTonomat.h"
#include "ServiceUtilizator.h"

class UI {
private:
    ServiceTonomat& servicetonomat;
    ServiceUtilizator& serviceutilizator;
public:
    explicit UI(ServiceTonomat& servicetonomat, ServiceUtilizator& serviceutilizator);
    ~UI();
    void runMenu();
private:
    void uiaddTonomat();
    static void displayMenuGeneral();
    static void displayMenuTonomat();
    static void displayMenuUtilizator();

    template<class Entity>
    static void showAll(const vector<Entity>& entities);
    void uiUpdateTonomat();
    void uiDeleteTonomat();
    void handleProprietar();
    void runMenuTonomat();
    void handleUpdateSold();

    void handleShowSold();

    void handleUtilizator();

    void handleCumparaProdus();

    void handleGetRest(int rest, int &cincizeci, int &zece);
    static int handleGetPretInMonede(float pret);
};


#endif //LAB9_10_UI_H
