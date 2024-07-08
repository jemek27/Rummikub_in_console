//
// Created by jemek on 18.06.2023.
//

#include "../headers/OdczytZapisyDoPliku.h"

void OdczytZapisyDoPliku::zapisTabZwy(const std::vector<std::string> &wiersz, const std::string &nazwaPliku) {
    std::ofstream plik(nazwaPliku, std::ios_base::app); // Otwieramy plik w trybie dopisywania
    if (plik.is_open()) {
        for (const auto &element: wiersz) {
            plik << element << " ";
        }
        plik << "\n";
        plik.close();
//        std::cout << "Wiersz zostal zapisany do pliku: " << nazwaPliku << std::endl;
    } else {
        std::cerr << "Nie mozna otworzyc pliku: " << nazwaPliku << std::endl;
    }
}

std::vector<std::vector<std::string>> OdczytZapisyDoPliku::odczytWszystkichTabZwy(const std::string &nazwaPliku) {
    std::vector<std::vector<std::string>> data;
    std::ifstream plik(nazwaPliku);
    if (plik.is_open()) {
        std::string linijka;
        while (std::getline(plik, linijka)) {
            std::istringstream iss(linijka);
            std::vector<std::string> wiersz;
            std::string element;
            while (iss >> element) {
                wiersz.push_back(element);
            }
            data.push_back(wiersz);
        }
        plik.close();
//        std::cout << "Dane zostaly odczytane z pliku: " << nazwaPliku << std::endl;
    } else {
        std::cerr << "Historia jest pusta. Po rozegranej rozgrywce sprobuj ponownie." << nazwaPliku << std::endl;
    }
    return data;
}

void OdczytZapisyDoPliku::WyczyscPlik(const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku, std::ios::trunc); // Otwieramy plik w trybie czyszczenia (truncation)
    if (plik.is_open()) {
        plik.close();
        std::cout << "Historia zostala wyczyszczona: " << std::endl;
    } else {
        std::cerr << "Nie mozna otworzyc pliku: " << nazwaPliku << std::endl;
    }
}
