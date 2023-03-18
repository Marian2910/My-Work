#include "Headers/teste.h"
#include "Headers/ServiceTonomat.h"
#include "Headers/ServiceUtilizator.h"
#include "Headers/RepositoryGeneric.h"
#include "Headers/UI.h"

int main() {
    testAll();
    RepositoryGeneric<Tonomat> repoTonomat("tonomat.csv");
//    RepositoryGeneric<Tonomat> repoTonomat;
//    RepositoryGeneric<Utilizator> repoUtilizator;
    RepositoryGeneric<Utilizator> repoUtilizator("utilizator.csv");
    ServiceTonomat serviceTonomat(repoTonomat);
    ServiceUtilizator serviceUtilizator(repoUtilizator);
    UI ui(serviceTonomat, serviceUtilizator);

//    serviceTonomat.addSold("001", "CocaCola", 4.50, 100, 250);
//    serviceTonomat.addProdus("002", "Pepsi", 4.30);
//    serviceTonomat.addProdus("003", "M&M's", 3.80);
//    serviceTonomat.addProdus("004", "KinderBueno", 5.30);
//    serviceTonomat.addProdus("005", "AquaCarpatica", 2.50);
//    serviceTonomat.addProdus("006", "Nutline", 3.90);

    ui.runMenu();




    return 0;
}
