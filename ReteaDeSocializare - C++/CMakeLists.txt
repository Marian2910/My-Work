cmake_minimum_required(VERSION 3.21)
project(ReteaDeSocializare)

set(CMAKE_CXX_STANDARD 14)

add_executable(ReteaDeSocializare main.cpp Domain/Utilizator.cpp Domain/Utilizator.h Domain/Prietenie.cpp Domain/Prietenie.h Domain/Mesaj.cpp Domain/Mesaj.h Repository/TADArray.h Service/ServiceUtilizator.cpp Service/ServiceUtilizator.h Service/ServicePrietenie.cpp Service/ServicePrietenie.h Service/ServiceMesaj.cpp Service/ServiceMesaj.h Retea/Retea.cpp Retea/Retea.h Repository/RepositoryUtilizator.h Repository/RepositoryPrietenie.h Repository/RepositoryMesaj.h Repository/RepositoryUtilizator.cpp Repository/RepositoryPrietenie.cpp Repository/RepositoryMesaj.cpp Tests/Tests.cpp Tests/Tests.h Repository/TADMultime.h)
