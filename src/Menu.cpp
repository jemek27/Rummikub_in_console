//
// Created by Ema on 30.04.2023.
//

#include "../headers/Menu.h"

Menu::Menu() {
    rozgrywka = true;
    rundaTrwa = true;
    nazwaZapisu = "historiaZwyciezcow";
}

bool Menu::przywitanie() {
    std::cout << "\nWitaj w grze EmaKu... znaczy Rummikub!\n";
    while (rundaTrwa){
        std::cout << "Dostepne opcje:\nc - sterowanie/controls\nr - zasady/rules\np - graj/play\nh - historia/history\ne - wyjscie/exit \n";
        std::string wybor;
        std::cin >> wybor;
        if (wybor == "CLEAR_HISTORY") {
            odczytZapis.WyczyscPlik(nazwaZapisu);
        } else {
            switch (toupper(wybor[0])) {
                case 'P':
                    rundaTrwa = true;
                    return true;
                case 'C':
                    wyswietlSterowanie();
                    break;
                case 'R':
                    wyswietlZasady();
                    break;
                case 'E':
                    rundaTrwa = false;
                    rozgrywka = false;
                    return false;
                case 'H':
                    oczytajWyswietlHisZwy();
                    break;
                default:
                    std::cout << "Dany znak nie odpowiada zadnej komendzie";
            }
        }
    }
    return false;
}


void Menu::wyswietlSterowanie() {
    std::cout << "\nsterowanie\n";
    std::cout
            << "Komenda wylozenia: <nr ciagu>-<idetyfikator zetonu> np.  3-01B  |  2-11G  |  11-J  |  9-JK  |  11-2R\n"
            <<
            "Komenda wylozenia z JK: np. <2-JK> i potem watosc jaka ma przyjac np. 11R.\n" <<
            "Komenda nowy - new: <n>-<idetyfikator zetonu> np.  n-1G  |  n-11B \n" <<
            "Komenda wez - take: <t><nr ciagu>-<nr zetonu (pierwszy, drugi)> np.  -(1)-[2R][JK][4R]  t1-2  = bierzemy JK\n"
            <<
            "Komenda dziel ciag - divide: <d><nr ciagu>-<nr zetonu po ktorym dzielimy> np.  -(1)-[2R][JK][4R][5R][6R] d1-3 = -(1)-[2R][JK][4R] -(2)-[5R][6R]\n"
            <<
            "Komenda poloncz ciagi - merge: <m><nr ciagu>-<nr ciagu z ktorym lonczymy> np.  -(1)-[2B][JK][4B] -(2)-[5B][6B][7B] m1-2 = -(1)-[2B][JK][4B][5B][6B][7B]\n"
            <<
            "Mozna laczyc komendy za pomoca ; np. n-11g;3-11y;3-11r;d4-1 lub 1-jk;1-jk;1-jk\n" <<
            "Komenda zakoncz ture - finish: <f>\n" <<
            "Komenda poddaj sie: <surr>\n\n";
}

void Menu::wyswietlZasady() {
    std::cout << "\nZasady dostepne na: https://rummikub.pl/instrukcje/\n\n";
}

std::vector<std::string> Menu::iloscGraczy() {
    std::string ilosc;
    std::vector<std::string> gracze;
    bool zlaLiczba = true;
    int pierwszeWypisanie = 0; // po dodaniu std::getline, zrobił się problem, że podwojenie wypisuje

    while (zlaLiczba) {
        if (pierwszeWypisanie++ > 0) {std::cout << "Wybierz ilosc graczy z przedzialu 2-4" << std::endl;}
        std::getline(std::cin, ilosc);
        if (ilosc.size() == 1 and (ilosc[0] >= 50 and ilosc[0] <= 52)) {zlaLiczba = false;}
    }
    int ile = stoi(ilosc);

    std::cout
            << "Wpisz nazwe pierwszego gracza. Mozesz wpisac litere <n> jesli nie chcesz nadawac znaw graczom.\n";
    std::string wyborCzyNazwy;
    std::getline(std::cin, wyborCzyNazwy);

    if ((tolower(wyborCzyNazwy[0]) == 'n' and wyborCzyNazwy.size() == 1) or wyborCzyNazwy.size() == 0) {
        //nazwami będą cyfra
        for (int i = 0; i < ile; i++) {
            gracze.push_back(std::to_string(i + 1));
        }
    } else {
        ZamienSapcjeNaPodlogi(wyborCzyNazwy);
        gracze.push_back(wyborCzyNazwy);
        for (int i = 1; i < ile; i++) {
            std::string nazwaGracza;

            std::cout << "Wpisz nazwe graczar nr. " << i + 1 << "\n";
            std::getline(std::cin, nazwaGracza);
            ZamienSapcjeNaPodlogi(nazwaGracza);
            gracze.push_back(nazwaGracza);
        }
    }
    return gracze;
}

void Menu::wypiszTabZwyciezcow(std::vector<int> tabela, const std::vector<std::string> &nazwyGraczy) {

    int najdlNazwa = 0;
    for (const auto &nazwaGr: nazwyGraczy) {
        if (nazwaGr.size() > najdlNazwa) { najdlNazwa = nazwaGr.size(); }
    }

    if (!tabela.empty()) {
        aktualniZwy.clear();
        std::cout << "\n\n~~~TABELA ZWYCIEZCOW~~~\n\n";
        int poprzniNrRundy = tabela[0];
        int poprzenieMiejsce = 1;
        int Miejsce = 1;
        std::pair<std::string,int> nrRundaNazwa;
        std::vector<int> poddaliSie;

        for (int i = 0; i < tabela.size() / 2; i++) { //runda tabela[2 * i]   | nrGR[(2 * i) + 1]


            if (tabela[2 * i] > 0) {
                if (poprzniNrRundy == tabela[2 * i]) {
                    nrRundaNazwa = {zNrDoNazwy(tabela[(2 * i) + 1], nazwyGraczy), poprzenieMiejsce};
                    std::cout << poprzenieMiejsce << ". Gracz: " << nrRundaNazwa.first << "\n";
                    aktualniZwy.push_back(nrRundaNazwa);
                    Miejsce++;
                } else {

                    nrRundaNazwa= {zNrDoNazwy(tabela[(2 * i) + 1], nazwyGraczy), Miejsce};
                    std::cout << Miejsce << ". Gracz: " << nrRundaNazwa.first << "\n";
                    aktualniZwy.push_back(nrRundaNazwa);
                    poprzenieMiejsce = Miejsce++;
                    poprzniNrRundy = tabela[2 * i];

                }
            } else {
                poddaliSie.push_back(tabela[(2 * i) + 1] + 1);
            }

        }

        for (auto surr: poddaliSie) {
            nrRundaNazwa = {zNrDoNazwy(surr - 1, nazwyGraczy), Miejsce};
            std::cout << Miejsce << ". Gracz: " << nrRundaNazwa.first << "\n";
            aktualniZwy.push_back(nrRundaNazwa);
        }
        std::cout << "\n";
    }
    zapiszZwy();
}

std::string Menu::zNrDoNazwy(const int &nr, const std::vector<std::string> &nazwyGraczy) {
    switch (nr) {
        case 1:
            return nazwyGraczy[0];
        case 2:
            return nazwyGraczy[1];
        case 3:
            return nazwyGraczy[2];
        case 4:
            return nazwyGraczy[3];
        default:
            return {}; //tak w razie czego
    }
}

void Menu::zapiszZwy() {
    std::vector<std::string> tempWektor;
    for (const auto& para : aktualniZwy) {
        tempWektor.push_back(std::to_string(para.second));
        tempWektor.push_back(para.first);
    }
    odczytZapis.zapisTabZwy(tempWektor, nazwaZapisu);
}

void Menu::oczytajWyswietlHisZwy() {
    std::cout << "\n\n~~~HISTORIA ZWYCIEZCOW~~~\n\n";

    std::vector<std::vector<std::string>> zaladowaneDane = odczytZapis.odczytWszystkichTabZwy(nazwaZapisu);
    int licznik = 1;
    for (const auto& wiersz : zaladowaneDane) {
        std::cout << licznik++ << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        for (int i = 0; i < wiersz.size(); i += 2) {
            std::cout << wiersz[i] << ". Gracz: " << wiersz[i+1] << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "Aby wyczyscic historie wpisz <CLEAR_HISTORY>\n";
}

void Menu::ZamienSapcjeNaPodlogi(std::string &text) {
    for (char& c : text) {
        if (c == ' ') {
            c = '_';
        }
    }
}

