//
// Created by Marian Mutu on 28.04.2022.
//

#include "Retea.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


Retea::Retea(ServiceUtilizator &serviceutilizator, ServicePrietenie &serviceprietenie, ServiceMesaj &servicemesaj):
    serviceutilizator(serviceutilizator), serviceprietenie(serviceprietenie), servicemesaj(servicemesaj ){}

Retea::~Retea() = default;

void Retea::runMenu() {
   while(true){
       displayMenu();
       string cmd;
       cout<<"Introduceti o comanda: ";
       cin>>cmd;
       if(cmd == "1"){
           try {
           uiaddUtilizator();
           }
           catch (exception &exc) {
               cout << "Exception: " << exc.what() << endl;
           }
       }
       else if(cmd == "2") {
           try {
               uihandleConectare();
           }
           catch (exception &exc) {
               cout << "Exception: " << exc.what() << endl;
           }
       }
       else if(cmd == "3")
           uisearch();
       else if(cmd == "4")
           uishowUtilizatori();
       else if(cmd == "x")
           exit(EXIT_SUCCESS);
       else
           cout<<"Comanda invalida, reincercati: ";

   }
}

void Retea::displayMenu() {
    cout<<"MENIU \n"
          "1. Creeare cont \n"
          "2. Conectare \n"
          "3. Cauta-ti Id-ul \n"
          "4. Arata toti utilizatorii \n"
          "x. Inchiderea aplicatiei \n";
}



void Retea::uiaddUtilizator() {
    string id, nume, prenume;
    cout<<"id: ";
    cin>>id;
    cout<<"nume: ";
    cin>>nume;
    cout<<"prenume: ";
    cin>>prenume;
    if(id.empty())
        throw exception();
    if(nume.empty())
        throw exception();
    if(prenume.empty())
        throw exception();
    for(int i=0; i<serviceutilizator.getAll().size(); i++) {
        if(id == serviceutilizator.getAll()[i].getId()) {
            cout << "Exista deja un utilizator cu id-ul " << id << " \n";
            return;
        }
    }
    serviceutilizator.addUtilizator(id, nume, prenume);
}

void Retea::uishowUtilizatori() {
    for(int i = 0; i < serviceutilizator.getAll().size(); i++)
        cout<<serviceutilizator.getAll()[i];
}

void Retea::uideleteUtilizator(const string &id) {
    servicemesaj.deleteMesaj(id);
    serviceprietenie.deleteAllPrietenie(id);
    serviceutilizator.deleteUtilizator(id);
}

void Retea::uiupdateUtilizator(const string &id) {
    string nume, prenume;
    cout<<"Noul nume: ";
    cin>>nume;
    cout<<"Noul prenume: ";
    cin>>prenume;
    if(nume.empty())
        throw exception();
    if(prenume.empty())
        throw exception();
    serviceutilizator.updateUtilizator(id, nume, prenume);
}

void Retea::uiaddPrietenie(const string &id) {
    string idPrieten;
    cout<<"Pentru a creea o prietenie introduceti id-ul utilizatorului (folositi comanda search pentru a gasi id-ul) \n";
    cout<<"id: ";
    cin>>idPrieten;
    if(serviceprietenie.prietenieExistenta(id, idPrieten)) {
        cout<<"Sunteti deja prieteni. \n";
        return;
    }
    if(serviceutilizator.getUtilizatorDupaId(idPrieten).getId() != "err")
        serviceprietenie.addPrietenie(id, idPrieten);
    else
        cout<<"Nu exista nici un utilizator cu id-ul "<<idPrieten<<"\n";

}

void Retea::uideletePrietenie(const string &id) {
    string idPrieten;
    cout<<"Introduceti id-ul prietenului pe care doriti sa-l stergeti: ";
    cin>>idPrieten;
    serviceprietenie.deletePrietenie(id, idPrieten);
}

void Retea::uishowPrietenie(const string &id) {
    for(int i=0 ; i<serviceprietenie.getAll().size();i++) {
        if (serviceprietenie.getAll().getElem(i).getId1() == id && serviceprietenie.getAll().getElem(i).getId1() != "err")
            cout << serviceutilizator.getUtilizatorDupaId(serviceprietenie.getAll().getElem(i).getId2());
        else if (serviceprietenie.getAll().getElem(i).getId2() == id && serviceprietenie.getAll().getElem(i).getId2() != "err")
            cout << serviceutilizator.getUtilizatorDupaId(serviceprietenie.getAll().getElem(i).getId1());
    }
}

void Retea::uihandlemessages(const string &id) {
    while (true) {
        uishowPrietenie(id);
        cout<<"b. back \n";
        string idPrieten;
        cout << "Introduceti id-ul prietenului caruia ii trimiteti mesaj: ";
        cin >> idPrieten;
        if (serviceutilizator.getUtilizatorDupaId(id).getId() == "err")
            cout << "Nu exista nici un utilizator cu id-ul introdus \n";
        else if (serviceprietenie.prietenieExistenta(id, idPrieten))
            uihandleConversation(id, idPrieten);
        else
            cout << "Nu sunteti prieteni, adaugati-l mai intai in lista de prieteni. \n";
        if(idPrieten == "b")
            break;
    }
}

void Retea::displayMenuUtilizator() {
    cout<<"1. Creeaza o prietenie \n"
          "2. Afiseaza toate prieteniile tale \n"
          "3. Sterge o prietenie \n"
          "4. Search \n"
          "5. Chat messages \n"
          "6. Contul meu \n"
          "d. Deconectare \n";
}

void Retea::uihandleConectare() {
    string password, prenume;
    cout<<"User: ";
    cin>> prenume;
    cout<<"Parola (id-ul dvs unic): ";
    cin>> password;
    for(int i=0; i < serviceutilizator.getAll().size(); i++)
        if(password == serviceutilizator.getAll()[i].getId() && prenume == serviceutilizator.getAll()[i].getPrenume()) {
            cout << "Logare reusita! \n";
            runMeniuUtilizator(password);
            return;
        }
    cout<<"Nume sau Id incorect, foloseste optiunea search pt a gasi id-ul \n";
}

void Retea::runMeniuUtilizator(const string &id) {
    while(true){
        string cmd;
        displayMenuUtilizator();
        cout<<"Introduceti o comanda: ";
        cin>>cmd;
        if(cmd == "1")
            uiaddPrietenie(id);
        else if(cmd == "2")
            uishowPrietenie(id);
        else if(cmd == "3")
            uideletePrietenie(id);
        else if(cmd == "4")
            uisearch();
        else if(cmd == "5")
            uihandlemessages(id);
        else if(cmd == "6")
            handleContulMeu(id);
        else if(cmd == "d")
            break;
        else
            cout<<"Comanda invalida, reincercati. \n";
    }
}

void Retea::uisearch() {
    string nume, prenume, id;
    cout<<"Introduceti numele: ";
    cin>>nume;
    cout<<"Introduceti prenumele: ";
    cin>>prenume;
    cout<<"Id-ul utilizatorului cu numele "<<nume<<" "<<prenume<<" este: "<<serviceutilizator.getIdUtilizator(nume, prenume)<<"\n";
}

void Retea::handleContulMeu(const string &id) {
    while(true){
        displayMenuContulMeu();
        string cmd;
        cout<<"Introduceti o comanda: ";
        cin>>cmd;
        if(cmd == "1")
            uiupdateUtilizator(id);
        else if(cmd == "2") {
            cout<<"Sunteti sigur ca doriti sa stergeti contul? (da/nu) ";
            cin>>cmd;
            if(cmd == "da") {
                uideleteUtilizator(id);
                cout<<"Cont sters, dupa deconectare va fi sters definitiv. \n";
                break;
            }
            else
                break;
        }
        else if(cmd == "b")
            break;
        else
            cout<<"Comanda invalida! \n";

    }

}

void Retea::displayMenuContulMeu() {
    cout<<"1. Modifica datele \n"
          "2. Sterge contul \n"
          "b. Inapoi \n";
}

void Retea::uiaddMesaj(const string &ide, const string& idd) {
    string mesaj;
    cout<<"mesaj: ";
    cin.ignore();
    getline(cin, mesaj);
    servicemesaj.addMesaj(ide, idd, mesaj);
    cout<<"Mesaj trimis cu succes \n";
}

void Retea::uihandleConversation(const string &id, const string& idPrieten) {

    for (int i = 0; i < servicemesaj.getConversatie(id, idPrieten).size(); i++)
        cout << " " << serviceutilizator.getUtilizatorDupaId(servicemesaj.getConversatie(id, idPrieten)[i].first).getPrenume() <<" : "<<servicemesaj.getConversatie(id, idPrieten)[i].second << "\n";
    while (true) {
        string cmd;
        cout<<"1. add / 2. exit \n";
        cin>>cmd;
        if(cmd == "1")
            uiaddMesaj(id, idPrieten);
        else if(cmd == "2")
            break;
        else
            cout<<"Comanda invalida! \n";
    }
}

