
#include "Repository/RepositoryUtilizator.h"
#include "Repository/RepositoryMesaj.h"
#include "Repository/RepositoryPrietenie.h"
#include "Service//ServiceUtilizator.h"
#include "Service//ServicePrietenie.h"
#include "Service//ServiceMesaj.h"
#include "Retea/Retea.h"
#include "Tests/Tests.h"


int main() {
    test_all();

    RepositoryUtilizator repoUtilizator("utilizatori.csv");
    RepositoryPrietenie repoPrietenie("prietenii.csv");
    RepositoryMesaj repoMesaje("mesaje.csv");
    ServiceUtilizator serviceUtilizator(repoUtilizator);
    ServicePrietenie servicePrietenie(repoPrietenie);
    ServiceMesaj serviceMesaje(repoMesaje);
    Retea retea(serviceUtilizator, servicePrietenie, serviceMesaje);

    retea.runMenu();



    return 0;
}
