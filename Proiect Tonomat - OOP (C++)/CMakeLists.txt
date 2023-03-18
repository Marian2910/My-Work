cmake_minimum_required(VERSION 3.21)
project(lab9_10)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab9_10 main.cpp Sources/Produse.cpp Headers/Produse.h Sources/Utilizator.cpp Headers/Utilizator.h Sources/teste.cpp Headers/teste.h Sources/UI.cpp Headers/UI.h Sources/ServiceUtilizator.cpp Headers/ServiceUtilizator.h Headers/RepositoryGeneric.h Sources/Tonomat.cpp Headers/Tonomat.h Sources/Monede.cpp Headers/Monede.h Sources/ServiceTonomat.cpp Headers/ServiceTonomat.h Headers/Exception.h Headers/Validation.h)
