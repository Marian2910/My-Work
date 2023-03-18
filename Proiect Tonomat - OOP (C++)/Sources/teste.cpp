//
// Created by Marian Mutu on 16.04.2022.
//

#include "../Headers/teste.h"
#include "../Headers/Produse.h"
#include "../Headers/RepositoryGeneric.h"
#include "../Headers/ServiceTonomat.h"

void testTonomat(){
    Tonomat t1("001", "CocaCola", 4.50);
    Tonomat t2("002", "Pepsi", 4.50);
    Tonomat t3("003", "M&M's", 3.50);
    Tonomat t4("004", "KinderBueno", 5.20);
    Tonomat t5("005", "AquaCarpatica", 2.50);
    Tonomat t6("006", "Nutline", 3.80);
    Tonomat t7;
    t7 = t1;
    assert(t1.getNume() == "CocaCola");
    assert(t3.getCod() == "003");
    assert(t5.getPret() == 2.50);
    assert(t1  == t7);
}
void testRepo(){
    Tonomat t1("001", "CocaCola", 4.50);
    Tonomat t2("002", "Pepsi", 4.30);
    Tonomat t3("003", "M&M's", 3.70);
    Tonomat t4("004", "KinderBueno", 5.20);
    Tonomat t5("005", "AquaCarpatica", 2.50);
    Tonomat t6("006", "Nutline", 3.90);
//    RepositoryGeneric<Tonomat> testRepo("testRepo.csv");
    RepositoryGeneric<Tonomat> testRepo;
    testRepo.addElem(t1);
    testRepo.addElem(t2);
    testRepo.addElem(t3);
    testRepo.addElem(t4);
    testRepo.addElem(t5);
    testRepo.addElem(t6);
    assert(testRepo.getAll().size() == 6);
    testRepo.deleteElem(t3);
    testRepo.deleteElem(t5);
    assert(testRepo.getAll().size() == 4);
    testRepo.updateElem(t2, t6);
    assert(testRepo.getAll()[1] == t6);
}

void testService(){
    RepositoryGeneric<Tonomat> testRepo;
//    RepositoryGeneric<Tonomat> testRepo("testTonomatRepo.csv");
    ServiceTonomat testService(testRepo);
    testService.addProdus("001", "CocaCola", 4.50);
    testService.addProdus("002", "Pepsi", 4.30);
    testService.addProdus("003", "M&M's", 3.80);
    testService.addProdus("004", "KinderBueno", 5.20);
    testService.addProdus("005", "AquaCarpatica", 2.50);
    testService.addProdus("006", "Nutline", 3.90);

    assert(testService.getAll().size() == 6);

    testService.deleteProdus("003");
    testService.deleteProdus("004");
    testService.deleteProdus("005");

    assert(testService.getAll().size() == 3);

    testService.updateProdus("002", "Fanta", 4.30);
    assert(testService.getAll()[1].getNume() == "Fanta");


}

void testFunctionalitate(){
    RepositoryGeneric<Tonomat> testRepo;
    ServiceTonomat testService(testRepo);
    testService.addSold("001", "CocaCola", 4.50, 50, 40);
    testService.addProdus("002", "Pepsi", 4.30);
    testService.addProdus("003", "M&M's", 3.80);
    testService.addProdus("004", "KinderBueno", 5.20);
    testService.addProdus("005", "AquaCarpatica", 2.50);
    testService.addProdus("006", "Nutline", 3.90);

    assert(testService.showSold() == 2900);

    testService.addToSold(20, 10);

    assert(testService.showSold() == 4000);

}

void testAll(){
    testTonomat();
    testRepo();
    testService();
    testFunctionalitate();
    }