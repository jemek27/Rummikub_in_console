//
// Created by jemek on 18.06.2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#ifndef RUMMIKUB_ODCZYTZAPISYDOPLIKU_H
#define RUMMIKUB_ODCZYTZAPISYDOPLIKU_H


class OdczytZapisyDoPliku {
public:
    void zapisTabZwy(const std::vector<std::string>& wiersz, const std::string& nazwaPliku);
    std::vector<std::vector<std::string>> odczytWszystkichTabZwy(const std::string& nazwaPliku);
    void WyczyscPlik(const std::string& nazwaPliku);
};


#endif //RUMMIKUB_ODCZYTZAPISYDOPLIKU_H
