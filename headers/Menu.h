//
// Created by Ema on 30.04.2023.
//
#include <iostream>
#include <vector>
#include "OdczytZapisyDoPliku.h"

#ifndef RUMMIKUB_MENU_H
#define RUMMIKUB_MENU_H


class Menu {
    OdczytZapisyDoPliku odczytZapis;
    std::vector<std::pair<std::string, int>> aktualniZwy;
    std::string nazwaZapisu;
public:
    bool rundaTrwa;
    bool rozgrywka;

    Menu();
    bool przywitanie();
    static void wyswietlSterowanie();
    static void wyswietlZasady();
    std::vector<std::string> iloscGraczy();
    void wypiszTabZwyciezcow(std::vector<int> tabela, const std::vector<std::string> &nazwyGraczy);
    std::string zNrDoNazwy(const int &nr, const std::vector<std::string> &nazwyGraczy);
    void zapiszZwy();
    void oczytajWyswietlHisZwy();
    void ZamienSapcjeNaPodlogi(std::string& text);
};


#endif //RUMMIKUB_MENU_H
