#include <iostream>
#include <cctype>
#include "headers/WorekNaZetony.h"
#include "headers/Zeton.h"
#include "headers/TabliczkaGracza.h"
#include "headers/Plansza.h"
#include "headers/Menu.h"
#include "headers/ListaZetonow.h"
#include "headers/testowanie.h"


int main() {
//    ListaZetonow::testListy();
//    kolory();
//    odczytZapis();
//    testRozgrywki();
//    testOperatoryStrumieniowe();

    Menu menu;

    while (menu.rozgrywka) {
        int licznikTur = 0;
        menu.rundaTrwa = true;

        if (menu.przywitanie()) {
            std::vector<std::string> gracze  = menu.iloscGraczy();
            int  ileGR = gracze.size();
            WorekNaZetony testWorekNaZetony(ileGR);
            Plansza testPlasza(testWorekNaZetony, gracze);


            while (menu.rundaTrwa) { // do testu  and licznikTur != 2
                if (licznikTur++ == 0) menu.wyswietlSterowanie();

                for (int i = 0; i < ileGR; i++) {
                    testPlasza.kolejGracza(i, licznikTur);
                }
                if (testPlasza.iluSkonczylo() >= ileGR - 1 ) menu.rundaTrwa = false;
            }
            menu.wypiszTabZwyciezcow(testPlasza.dajTabZwy(), gracze);
        }

    }

    return 0;


}
