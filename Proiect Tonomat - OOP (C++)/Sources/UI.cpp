//
// Created by Marian Mutu on 25.04.2022.
//

#include "../Headers/UI.h"
#include "../Headers/Exception.h"
#include "../Headers/Validation.h"
#include <iostream>
using namespace std;

UI::UI(ServiceTonomat &servicetonomat, ServiceUtilizator& serviceutilizator): servicetonomat(servicetonomat), serviceutilizator(serviceutilizator) {}
UI::~UI() = default;
void UI::runMenu() {
    while(true){
        displayMenuGeneral();
        string cmd;
        cout<<"Introduceti o comanda: ";
        cin>>cmd;
        if(cmd == "1")
            handleUtilizator();
        else if(cmd == "2")
            handleProprietar();
        else if(cmd == "x")
            exit(EXIT_SUCCESS);
        else
            cout<<"Comanda invalida! \n";
    }

}


void UI::displayMenuGeneral() {
    cout<<"Meniu General: \n"
          "1. Client \n"
          "2. Proprietar \n"
          "x. Iesire \n";
}

void UI::displayMenuTonomat() {
    cout<<"Meniu Produse: \n"
          "1. Introduceti un produs in tonomat \n"
          "2. Modificati un produs existent \n"
          "3. Stergeti un produs din tonomat \n"
          "4. Afisati toate produsele existente \n"
          "5. Adauga monede \n"
          "6. Afisare sold \n"
          "b. Back \n";
}


void UI::displayMenuUtilizator() {
    cout<<"Meniu Client: \n"
          "1. Cumpara un produs \n"
          "2. Afiseaza lista cu produse \n"
          "i. Iesire \n";
}

void UI::uiaddTonomat() {
    string cod, nume, pret;
    int cincizeci, zece;
    cout<<"Introduceti cod-ul produsului: ";
    cin>>cod;
    cout<<"Introduceti numele produsului: ";
    cin>>nume;
    cout<<"Introduceti pretul produsului: ";
    cin>>pret;


    if(cod == "0")
        throw Validation("Codul nu poate fi 0!");
    if(nume == "0" || nume == "1" || nume == "2" || nume == "3" || nume == "4"|| nume == "5"|| nume == "6"|| nume == "7"|| nume == "8"|| nume == "9")
        throw Validation("Numele trebuie sa fie un string!");
    if(!stof(pret))
        throw Validation("Pretul nu poate fi negativ, sau string!");
    if(servicetonomat.getAll().empty()) {
        cout<<"Introduceti si monede in tonomat: \n";
        cout<<"de 50 bani: ";
        cin>>cincizeci;
        if(cincizeci < 0)
            throw Validation("Numarul monedelor de 50 de bani nu poate fi negativ!");
        cout<<"de 10 bani: ";
        cin>>zece;
        if(zece < 0)
            throw Validation("Numarul monedelor de 10 de bani nu poate fi negativ!");
        servicetonomat.addSold(cod, nume, stof(pret), cincizeci, zece);
    }
    else
        servicetonomat.addProdus(cod, nume, stof(pret));
}

template <class Entity>
void UI::showAll(const vector<Entity> &entities) {
    for(auto & i : entities)
        cout<<i;
}

void UI::uiUpdateTonomat() {
    string cod, nume, pret;
    cout<<"Introduceti cod-ul produsului pe care doriti sa-l modificati: ";
    cin>>cod;
    cout<<"Introduceti noul nume: ";
    cin>>nume;
    cout<<"Introduceti noul pret: ";
    cin>>pret;

    if(cod == "0")
        throw Validation("Codul nu poate fi 0!");
    if(nume == "0" || nume == "1" || nume == "2" || nume == "3" || nume == "4"|| nume == "5"|| nume == "6"|| nume == "7"|| nume == "8"|| nume == "9")
        throw Validation("Numele trebuie sa fie un string!");
    if(stof(pret) < 0)
        throw Validation("Pretul nu poate fi negativ!");

    servicetonomat.updateProdus(cod, nume, stof(pret));
}

void UI::uiDeleteTonomat() {
    string cod;
    cout<<"Introduceti cod-ul produsului pe care doriti sa-l stergeti: ";
    cin>>cod;
    if(cod == "0")
        throw Validation("Codul nu poate fi 0!");
    servicetonomat.deleteProdus(cod);
}

void UI::handleProprietar() {
    int pin, incercari = 2;
    cout<<"Introduceti codul PIN: ";
    cin>>pin;
    while(pin != 1234 && incercari != 0) {
        cout<<"PIN gresit introdus, mai aveti "<<incercari<<"/3 incercari:  \n";
        incercari--;
        cin>>pin;
    }
    if(incercari == 0)
        return;


    runMenuTonomat();

}

void UI::runMenuTonomat() {

    while(true){
        displayMenuTonomat();
        string comanda;
        cout<<"Introduceti o comanda: ";
        cin>>comanda;
        if(comanda == "1") {
            try {
                uiaddTonomat();
            }
            catch (int &exc) {
                cout << "Exception: " << exc << endl;
            }
            catch (Exception &exc) {
                cout << "Exception: " << exc.getMessage() << endl;
            }
            catch (Validation &err) {
                cout << "Validation: " << err.getMessage() << endl;
            }
        }
        else if(comanda == "2") {
            try {
                uiUpdateTonomat();
            }
            catch (int &exc) {
                cout << "Exception: " << exc << endl;
            }
            catch (Exception &exc) {
                cout << "Exception: " << exc.getMessage() << endl;
            }
            catch (Validation &err) {
                cout << "Validation: " << err.getMessage() << endl;
            }
        }
        else if(comanda == "3") {
            try {
                uiDeleteTonomat();
            }
            catch (int& exc) {
                cout << "Exception: " << exc << endl;
            }
            catch (Exception& exc) {
                cout << "Exception: " << exc.getMessage() << endl;
            }
        }
        else if(comanda == "4") {
            showAll(this->servicetonomat.getAll());
            handleShowSold();
        }
        else if(comanda == "5"){
            try {
                handleUpdateSold();
            }
            catch (int& exc) {
                cout << "Exception: " << exc << endl;
            }
            catch (Exception& exc) {
                cout << "Exception: " << exc.getMessage() << endl;
            }
        }
        else if(comanda == "6")
            handleShowSold();
        else if(comanda == "b")
            break;
        else
            cout<<"Comanda invalida! \n";
    }
}

void UI::handleUpdateSold() {
    int cincizeci, zece;
    cout<<"Introduceti noul sold: \n";
    cout<<"monede de 50 bani: \n";
    cin>>cincizeci;
    if(cincizeci < 0){
        throw Exception("Numarul monedelor de 50 de bani nu poate fi negativ!");
    }
    cout<<"monede de 10 bani: \n";
    cin>>zece;
    if(zece < 0){
        throw Exception("Numarul monedelor de 10 bani nu poate fi negativ!");
    }
    if(servicetonomat.getAll().empty())
        cout<<"Tonomatul nu are produse, adaugati mai intai produse in lista! \n";
    else
        servicetonomat.updateSold(cincizeci, zece);

}

void UI::handleShowSold() {
    if(servicetonomat.getAll().empty())
        cout<<"Tonomatul nu are produse, adaugati mai intai produse in lista! \n";
    else
        cout<<"Soldul este : \n"
              "monede de 50: "<<servicetonomat.getAll()[0].getMonede().getCinzeciBani()<<endl<<
              "monede de 10: "<<servicetonomat.getAll()[0].getMonede().getZeceBani()<<endl;
}

void UI::handleUtilizator() {
    while(true){
        displayMenuUtilizator();
        string comanda;
        cout<<"Introduceti o comanda: ";
        cin>>comanda;
        if(comanda == "1") {
            try {
                handleCumparaProdus();
            }
            catch (int &exc) {
                cout << "Exception: " << exc << endl;
            }
            catch (Exception &exc) {
                cout << "Exception: " << exc.getMessage() << endl;
            }
            catch (Validation &err) {
                cout << "Validation: " << err.getMessage() << endl;
            }
        }
        else if(comanda == "2")
            showAll(this->servicetonomat.getAll());
        else if(comanda == "i")
            break;
        else
            cout<<"Comanda invalida! \n";
    }
}

void UI::handleCumparaProdus() {
    int cincizeci, zece, sold, pretMonede, ok = 0;
    string cod;
    cout << "Introduceti monede (50/10 bani): \n";
    cout << "de 50 de bani: ";
    cin >> cincizeci;
    cout << "de 10 de bani: ";
    cin >> zece;
    cout << "Introduceti codul produsului: ";
    cin >> cod;

    if(cincizeci < 0)
        throw Validation("Numarul monedelor de 50 de bani nu poate fi negativ!");
    if(zece < 0)
        throw Validation("Numarul monedelor de 10 de bani nu poate fi negativ!");
    if(cod == "0")
        throw Validation("Codul nu poate fi 0!");

    for(int i=0; i<servicetonomat.getAll().size();i++)
        if(servicetonomat.getAll()[i].getCod() == cod)
            ok = 1;
    if(ok == 0) {
        string msj = "Nu exista nici un produs cu cod-ul " + cod;
        throw Validation(msj.c_str());
    }


    sold = (50 * cincizeci) + (10 * zece);
    int rest50 = 0, rest10 = 0;
    for (auto i: servicetonomat.getAll())
        if (i.getCod() == cod) {
            pretMonede = handleGetPretInMonede((float) i.getPret());
            if (sold < pretMonede) {
                cout << "monede insuficiente, operatiunea nu a avut loc! \n";
                serviceutilizator.addUtilizator(((float)cincizeci/2) + ((float)zece/10), cod);
            }
            else if (sold > pretMonede) {
                handleGetRest(sold - pretMonede, rest50, rest10);
                if (rest50 == 0 && rest10 == 0)
                    cout << "Tonomatul nu are monede suficiente; \n";
                else
                    cout << "Tranzactie acceptata, restul dvs. este: " << rest50 << " x50 si " << rest10 << " x10;"
                         << "\n";
                serviceutilizator.addUtilizator(((float)cincizeci/2) + ((float)zece/10), cod);
                cincizeci = cincizeci - rest50;
                zece = zece - rest10;
                servicetonomat.addToSold(cincizeci, zece);
            } else if (sold == pretMonede) {
                cout << "Tranzactie acceptata, rest 0. \n";
                servicetonomat.addToSold(cincizeci, zece);
                serviceutilizator.addUtilizator(((float)cincizeci/2) + ((float)zece/10), cod);
            }
    }
}

void UI::handleGetRest(int rest, int &cincizeci, int &zece) {
    int monede50, monede10, suma = 0;
    cincizeci = 0;
    zece = 0;
    monede50 = servicetonomat.getAll()[0].getMonede().getCinzeciBani();
    monede10 = servicetonomat.getAll()[0].getMonede().getZeceBani();

    while(suma < rest) {
        suma = suma + 50;
        cincizeci++;
    }

    if(suma > rest) {
        suma = suma - 50;
        cincizeci--;
        while(suma < rest) {
            suma = suma + 10;
            zece ++;
        }
    }

    if(cincizeci > monede50  || zece > monede10 )
    {
        cincizeci = 0;
        zece = 0;
    }

}

int UI::handleGetPretInMonede(float pret) {
    int pretMonede = 0;
    while(pret > 1) {
        pret = pret - 1;
        pretMonede = pretMonede + 100;
    }
    if(pret < 1)
        pretMonede = pretMonede + int(pret * 100);
    return pretMonede;
}
