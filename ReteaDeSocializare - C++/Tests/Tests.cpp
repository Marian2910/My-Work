//
// Created by Marian Mutu on 20.05.2022.
//

#include "Tests.h"
#include "../Domain/Mesaj.h"
#include "../Domain/Prietenie.h"
#include "../Domain/Utilizator.h"
#include "../Repository/TADArray.h"
#include "../Repository/TADMultime.h"
#include "../Repository/RepositoryUtilizator.h"

void test_domain_tad(){
    Array<Utilizator> utilizatori;
    MultimeOrdonata<Utilizator> utilizatori_multime;
    Utilizator u0("101", "Pop", "Ioan");
    Utilizator u3("104", "Georges", "Ana");
    Utilizator u2("103", "Tulea", "Corina");
    Utilizator u1("102", "Daraban", "Triana");
    Utilizator u4("105", "Vasile", "Maria");
    utilizatori.push_back(u0);
    utilizatori.push_back(u1);
    utilizatori.push_back(u2);
    utilizatori.push_back(u3);
    utilizatori.push_back(u4);
    assert(utilizatori.size() == 5);
    assert(utilizatori.getElem(2) == u2);
    utilizatori.deleteElem(3);
    assert(utilizatori.size() == 4);
    utilizatori.setElemPos(2, u4);
    assert(utilizatori.getElem(2) == u4);
    utilizatori_multime.adauga(u0);
    utilizatori_multime.adauga(u1);
    utilizatori_multime.adauga(u2);
    utilizatori_multime.adauga(u3);
    utilizatori_multime.adauga(u4);
    assert(utilizatori_multime.get_lista_ordonata().size() == 5);
    assert(utilizatori_multime.get_lista_ordonata()[1] == u1);
}

void test_repo(){
    Utilizator u0("101", "Pop", "Ioan");
    Utilizator u1("102", "Georges", "Ana");
    Utilizator u2("103", "Tulea", "Corina");
    Utilizator u3("104", "Daraban", "Triana");
    Utilizator u4("105", "Vasile", "Maria");
    RepositoryUtilizator test_repo("test_repo.csv");
//    test_repo.addElem(u0);
//    test_repo.addElem(u1);
//    test_repo.addElem(u2);
//    test_repo.addElem(u3);
//    test_repo.addElem(u4);
cout<<test_repo.getAll().size();
    assert(test_repo.getAll().size() == 5);

}

void test_all(){
    test_domain_tad();
    test_repo();
}