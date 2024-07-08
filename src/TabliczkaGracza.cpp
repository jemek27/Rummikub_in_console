//
// Created by jemek on 21.04.2023.
//

#include "../headers/TabliczkaGracza.h"

TabliczkaGracza::TabliczkaGracza(WorekNaZetony &worek, int nrG) : nrGracza(nrG), pierszyRuch(true), skonczyl(false) {
    for (int i = 0; i < 14; i++) {
        tabliczka.push_back(worek.vectorZetonow.back());
        worek.vectorZetonow.pop_back();
    }
    tabliczka.sort([](Zeton *a, Zeton *b) { return *a < *b; });
}

TabliczkaGracza::TabliczkaGracza(WorekNaZetony &worek, int nrG, const std::string& nazwa) : nrGracza(nrG), pierszyRuch(true), skonczyl(false), nazwaGracza(nazwa){
    for (int i = 0; i < 14; i++) {
        tabliczka.push_back(worek.vectorZetonow.back());
        worek.vectorZetonow.pop_back();
    }
    tabliczka.sort([](Zeton *a, Zeton *b) { return *a < *b; });
}

TabliczkaGracza::~TabliczkaGracza() {
    for (auto pZ: tabliczka) delete pZ;
    for (auto pZ: podreczneZetony) delete pZ;
}

void TabliczkaGracza::pokazTabliczke() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!skonczyl){
        if (nazwaGracza.empty()) { std::cout << "Gracz: " << nrGracza << "\n{ "; }
        else { std::cout << nazwaGracza << ":\n{ "; }

        for (auto z: tabliczka) {
            if (z->cyfra != 0){ //nie joker
                z->pokazZeton();
                std::cout << " ";
            } else {
                SetConsoleTextAttribute(hConsole, 1);
                std::cout << "[JK] ";
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
        std::cout << "}";
        if (!podreczneZetony.empty()) {
            SetConsoleTextAttribute(hConsole, 13);

            std::cout << " | { ";
            for (auto z: podreczneZetony) {
                if (z->cyfra != 0){ //nie joker
                    z->pokazZeton();
                    std::cout << " ";
                } else {
                    SetConsoleTextAttribute(hConsole, 1);
                    std::cout << "[JK] ";
                    SetConsoleTextAttribute(hConsole, 13);
                }


            }
            SetConsoleTextAttribute(hConsole, 13);
            std::cout << "}";
            SetConsoleTextAttribute(hConsole, 7); // zmiana zwykłe
        }
        std::cout << "\n";
    }


}

TabliczkaGracza::TabliczkaGracza(TabliczkaGracza &inna) {
    for (auto pZ: inna.tabliczka) {
        if (pZ->cyfra) { //jeśli to JK to mamy 0
            tabliczka.push_back(new ZetonCyfra(pZ->idZetonu, pZ->cyfra, pZ->kolor));
        } else
            tabliczka.push_back(new Joker(pZ->idZetonu));
    }
    pierszyRuch = inna.pierszyRuch;
    nrGracza = inna.nrGracza;
    skonczyl = inna.skonczyl;
    nazwaGracza = inna.nazwaGracza;
}

std::pair<int, std::list<Zeton *>::iterator> TabliczkaGracza::jestZetonWTab(const std::string &komenda) {
    std::pair<int, std::list<Zeton *>::iterator> wynik;
    wynik.first = 0; // =false
    std::string ciag;
    std::string zeton;

    int idNr = 28; //inicjuje niegroźnymi wartościami
    char idKolor = 'b';

    bool jeszczeCiag = true;

    //np. 7-03C lub 11-1c
    for (auto c: komenda) {
        if (c == '-') jeszczeCiag = false;
        else if (jeszczeCiag) ciag.push_back(c);
        else zeton.push_back(c);
    }

    if (ciag.empty() or zeton.empty()) return wynik;

    //48-57 spr czy sa tylko cyfry
    for (auto c: ciag) {
        if (c < 48 or c > 57) return wynik;
    }

    if (toupper(zeton[0]) == 'J') {

        bool jestJK = false;
        bool jestWPodr = false;
        for (auto iter = podreczneZetony.begin(); iter != podreczneZetony.end(); iter++) {
            if (iter.operator*()->cyfra == 0 and iter.operator*()->kolor == '0') { //domyślne wartości temp dla JK
                jestJK = true;
                jestWPodr = true;
                wynik.first = stoi(ciag);
                wynik.second = iter;
                break;
            }
        }
        if (!jestWPodr) {
            for (auto iter = tabliczka.begin(); iter != tabliczka.end(); iter++) {
                if (iter.operator*()->cyfra == 0 and iter.operator*()->kolor == '0') { //domyślne wartości temp dla JK
                    jestJK = true;
                    wynik.first = stoi(ciag);
                    wynik.second = iter;
                    break;
                }
            }
        }


        if (jestJK) {
            std::string komendaJoker{"Mmm bigos"};
            bool niePoprawnaKomenda = true;
            std::string tempWartosc;

            // spr czy cyfra
            while (komendaJoker.size() < 2 or komendaJoker.size() > 4 or niePoprawnaKomenda) {
                std::cout << "Jaka wartosc chcesz nadac zetonowi? Wzor komendy --> 2B --> 11G\n";
                std::getline(std::cin, komendaJoker);
                tempWartosc = "";

                if (komendaJoker.size() == 2 and komendaJoker[0] >= 48 and komendaJoker[0] <= 57) {
                    tempWartosc = komendaJoker[0];
                    bool nadaniePowiodloSie = wynik.second.operator*()->nadajWartosciZetonowe(stoi(tempWartosc),
                                                                                              komendaJoker[1]);
                    niePoprawnaKomenda = !nadaniePowiodloSie;
                    if (niePoprawnaKomenda) std::cout << "Zla komenda\n";

                } else if (komendaJoker.size() == 3 and komendaJoker[0] >= 48 and komendaJoker[0] <= 57) {

                    for (int i = 0; i < 2; i++) {
                        if (komendaJoker[i] >= 48 and komendaJoker[i] <= 57) {

                            tempWartosc.push_back(komendaJoker[i]);
                        }
                    }

                    if (tempWartosc.size() == 2) {
                        bool nadaniePowiodloSie = wynik.second.operator*()->nadajWartosciZetonowe(stoi(tempWartosc),
                                                                                                  komendaJoker[2]);
                        niePoprawnaKomenda = !nadaniePowiodloSie;
                        if (niePoprawnaKomenda) std::cout << "Zla komenda\n";
                    } else std::cout << "Zla komenda\n";

                } else { std::cout << "Zla komenda\n"; }
            }
        }
        return wynik;

    } else {

        for (int i = 0; i < (zeton.size() - 1); i++) {
            if (zeton[i] < 48 or zeton[i] > 57) return wynik;
        }

        idNr = stoi(zeton);
        idKolor = zeton[zeton.size() - 1];


        for (auto iter = podreczneZetony.begin(); iter != podreczneZetony.end(); iter++) {
            if (iter.operator*()->cyfra == idNr and iter.operator*()->kolor == toupper(idKolor)) {
                wynik.first = stoi(ciag); // = true;
                wynik.second = iter;
                return wynik;
            }
        }

        for (auto iter = tabliczka.begin(); iter != tabliczka.end(); iter++) {
            if (iter.operator*()->cyfra == idNr and iter.operator*()->kolor == toupper(idKolor)) {
                wynik.first = stoi(ciag); // = true;
                wynik.second = iter;
                return wynik;
            }
        }
    }
    return wynik;
}



