//
// Created by jemek on 28.04.2023.
//

#include "../headers/Plansza.h"


void Plansza::pokazPlansze() {
    int i = 1;

    std::cout << "\n\n" << std::string(27, '~') << "\n";
    for (auto ciagi: wszystkieCiagi) {
        ciagi->ciagZetonow.sort([](Zeton *a, Zeton *b) { return *a < *b; });
        std::cout << "-(" << i++ << ")-";
        ciagi->pokazCiag();
    }
    std::cout << std::string(27, '~') << "\n" << "Tabliczki graczy:\n";

    for (auto tabGr: wszystkieTabGr)
        tabGr->pokazTabliczke();
    std::cout << std::string(27, '~') << "\n";
//    testkopi();
}

Plansza::~Plansza() {
    for (auto c: wszystkieCiagi) {
        delete c;
        c = nullptr;
    }

    for (auto t: wszystkieTabGr) {
        delete t;
        t = nullptr;
    }

    for (auto t: resztaZetonowWWorku) {
        delete t;
        t = nullptr;
    }

    if (kopiaZaposwaPlanszy) {
        delete kopiaZaposwaPlanszy;
        kopiaZaposwaPlanszy = nullptr;
    }
}

Plansza::Plansza(WorekNaZetony &worek, std::vector<std::string> nazwyGraczy) {
    if (nazwyGraczy[0] == "1") {//nie nadano nazw

        for (int i = 1; i <= nazwyGraczy.size(); i++) {
            auto tabGr = new TabliczkaGracza(worek, (i));
            wszystkieTabGr.push_back(tabGr);
        }

    } else {
        int i = 1;
        for (const auto& nazwa : nazwyGraczy) {
            auto tabGr = new TabliczkaGracza(worek, i++, nazwa);
            wszystkieTabGr.push_back(tabGr);
        }

    }


    for (auto resztaZetonow: worek.vectorZetonow) {
        resztaZetonowWWorku.push_back(resztaZetonow);
    }
    worek.vectorZetonow.clear();

    kopiaZaposwaPlanszy = nullptr;
    wszystkieCiagi.push_back(new CiagZetonow); //ciąg startowy
    pierwszeWykonanieKomendy = true;
    poprawnePierwszewylozenie = false;
}

Plansza::Plansza(const Plansza &inna) {
    for (CiagZetonow *ciag: inna.wszystkieCiagi) {
        wszystkieCiagi.push_back(new CiagZetonow(*ciag));
    }

    for (TabliczkaGracza *tabGr: inna.wszystkieTabGr) {
        wszystkieTabGr.push_back(new TabliczkaGracza(*tabGr));
    }

    for (auto resztaZetonow: inna.resztaZetonowWWorku) {
        if (resztaZetonow->cyfra != 0) {
            resztaZetonowWWorku.push_back(new ZetonCyfra(resztaZetonow->idZetonu, resztaZetonow->cyfra,
                                                         resztaZetonow->kolor));
        } else
            resztaZetonowWWorku.push_back(new Joker(resztaZetonow->idZetonu));
    }

    tabelaZwyciezcow = inna.tabelaZwyciezcow;
    pierwszeWykonanieKomendy = true;
    kopiaZaposwaPlanszy = nullptr;
    poprawnePierwszewylozenie = false;
}

Plansza::Plansza(TabliczkaGracza *tabGr) {
    wszystkieTabGr.push_back(new TabliczkaGracza(*tabGr));
    wszystkieCiagi.push_back(new CiagZetonow);
    pierwszeWykonanieKomendy = true;
    kopiaZaposwaPlanszy = nullptr;
    poprawnePierwszewylozenie = false;
}

Plansza &Plansza::operator=(const Plansza &inna) {
    if (this != &inna) {
        // Usuń poprzednie dane
        for (CiagZetonow *ciag: wszystkieCiagi) {
            delete ciag;
        }
        wszystkieCiagi.clear();

        for (TabliczkaGracza *tabGr: wszystkieTabGr) {
            delete tabGr;
        }
        wszystkieTabGr.clear();

        for (Zeton *zeton: resztaZetonowWWorku) {
            delete zeton;
        }
        resztaZetonowWWorku.clear();

        // Skopiuj nowe dane
        for (CiagZetonow *ciag: inna.wszystkieCiagi) {
            wszystkieCiagi.push_back(new CiagZetonow(*ciag));
        }

        for (TabliczkaGracza *tabGr: inna.wszystkieTabGr) {
            wszystkieTabGr.push_back(new TabliczkaGracza(*tabGr));
        }

        for (auto resztaZetonow: inna.resztaZetonowWWorku) {
            if (resztaZetonow->cyfra != 0) {
                resztaZetonowWWorku.push_back(new ZetonCyfra(resztaZetonow->idZetonu, resztaZetonow->cyfra,
                                                             resztaZetonow->kolor));
            } else
                resztaZetonowWWorku.push_back(new Joker(resztaZetonow->idZetonu));
        }

        tabelaZwyciezcow = inna.tabelaZwyciezcow;
    }

    return *this;
}

bool Plansza::czySkonczyl(const int idGr, const int nrRundy) {
    if (wszystkieTabGr[idGr]->tabliczka.empty()) {
        tabelaZwyciezcow.push_back(nrRundy);
        tabelaZwyciezcow.push_back(idGr + 1);
        wszystkieTabGr[idGr]->skonczyl = true;
        return true;
    }
    return false;
}

int Plansza::iluSkonczylo() {
    if (tabelaZwyciezcow.size() / 2 == wszystkieTabGr.size() - 1) {
        for (auto tabGr: wszystkieTabGr) { //możeliwe, że to nie potrzebne na z raczji na dodanie funkcji czyWygranaWlakowerem
            if (!tabGr->skonczyl) {
                tabGr->skonczyl = true;
                tabelaZwyciezcow.push_back(272727); //obojętna duża liczba, żeby ozanczyć walkowerowca
                tabelaZwyciezcow.push_back(tabGr->nrGracza);
            }
        }
    }
    return tabelaZwyciezcow.size() / 2;
}

std::vector<int> Plansza::dajTabZwy() {
    return tabelaZwyciezcow;
}

std::vector<std::string> Plansza::podzielKomendy(std::string komenda) {
    std::vector<std::string> wynik;
    std::string pojedynczaKomenda;
    komenda.push_back(';');

    for (auto c : komenda) {
        if (c == ';') {
            wynik.push_back(pojedynczaKomenda);
            pojedynczaKomenda = "";
        } else { pojedynczaKomenda.push_back(c); }
    }

    return wynik;
}

void Plansza::czyWygranaWlakowerem(int idGr, const int nrRundy) {
    if (wszystkieTabGr.size() - tabelaZwyciezcow.size() / 2 ==1 and !wszystkieTabGr[idGr]->skonczyl) { //jeśli liczba graczy - liczba graczy którzy skończyli
        tabelaZwyciezcow.push_back(nrRundy + 27);
        tabelaZwyciezcow.push_back(idGr + 1);
        wszystkieTabGr[idGr]->skonczyl = true;
    }
}


void Plansza::kolejGracza(int id, const int nrRundy) { //id od 0
    if (!wszystkieTabGr[id]->skonczyl) {

        kopiaZaposwaPlanszy = new Plansza(*this);
        std::vector<std::string> komendy;
        bool koniecTury = false;
        std::string komendaOG;
        int ileKomend = 0;

        while (!koniecTury) {
            if (!wszystkieTabGr[id]->pierszyRuch) {
                if (ileKomend == 0) {
                    pokazPlansze();

                    if (wszystkieTabGr[id]->nazwaGracza.empty()) {
                        std::cout << "Ruch gracza nr " << wszystkieTabGr[id]->nrGracza
                                  << "\nWpisz komende ruchu:\n";
                    } else {
                        std::cout << wszystkieTabGr[id]->nazwaGracza << " twoj ruch."
                                  << "\nWpisz komende ruchu:\n";
                    }

                    std::getline(std::cin, komendaOG);
                    komendy = podzielKomendy(komendaOG);
                    ileKomend = komendy.size();
                }
                for (auto komenda : komendy ) {
                    ileKomend--;

                    //po wykryciu, że dana komenda ma być wykonana, metoda ją wykonuje i zmienia pierwszeWykonanieKomendy na false
                    sprOgolnejPoprawnosciKomendy(id, komenda, koniecTury, nrRundy);
                    if (pierwszeWykonanieKomendy) {
                        KomendaDziel(komenda);
                        if (pierwszeWykonanieKomendy) {
                            KomendaLacz(komenda);
                            if (pierwszeWykonanieKomendy) {
                                KomendaNowy(komenda, id);
                                if (pierwszeWykonanieKomendy) {
                                    KomendaWez(komenda, id);
                                    if (pierwszeWykonanieKomendy) {
                                        KomendaRuch(komenda, id);
                                    }
                                }
                            }
                        }
                    }
                    if (ileKomend != 0) pierwszeWykonanieKomendy = true;

                }
            } else {
                pierwszeRuchGracza(id, nrRundy);
                koniecTury = true;
                break; //chyba niepotrzebne
            }
            pierwszeWykonanieKomendy = true;
        }
        delete kopiaZaposwaPlanszy;
        kopiaZaposwaPlanszy = nullptr;
    }
}

CiagZetonow *Plansza::podzielCiagi(CiagZetonow *pierwszyCiag, int poKtorym) {
    auto drugiCiag = new CiagZetonow;
    size_t poczatkowyRozmiar = pierwszyCiag->ciagZetonow.size();
    int licznik = 0;
    auto iter = pierwszyCiag->ciagZetonow.begin();

    int tempPoKtorym = poKtorym;
    while (tempPoKtorym--) iter++;

    std::copy(iter, pierwszyCiag->ciagZetonow.end(), std::back_inserter(drugiCiag->ciagZetonow));
    while (poczatkowyRozmiar - poKtorym > licznik) {
        licznik++;
        pierwszyCiag->ciagZetonow.pop_back();
    }
    return drugiCiag;
}


void Plansza::ruchGracza(const int &idGr, const int &nrCiagu, const std::list<Zeton *>::iterator iterZeton) {

    bool czyZPodrecznych = false;

    for (auto pZ : wszystkieTabGr[idGr]->podreczneZetony) {
        if (iterZeton.operator*()->idZetonu == pZ->idZetonu) czyZPodrecznych = true;
    }

    wszystkieCiagi[nrCiagu - 1]->ciagZetonow.push_back(*iterZeton);

    if (!czyZPodrecznych) wszystkieTabGr[idGr]->tabliczka.erase(iterZeton);
    else wszystkieTabGr[idGr]->podreczneZetony.erase(iterZeton);


}

/*
 * nie można manipulować żetonami na stole
 * więc stworzona zostanie osobna planasz na której gracz będzie mógł wykonać swoje pierwsze wyłożenie
 * jeśli będzie ok, to ciągi zostaną dodane do oryginału, a tab oryginału skopiowane z tamtej planszy
 */
void Plansza::pierwszeRuchGracza(const int &id, const int nrRundy) {
    std::cout << "Pierwsze wylozenie musi miec wspolna wartosc zetonow >=30\n";
    wszystkieTabGr[id]->pierszyRuch = false;

    Plansza pierwszeRuchPlansza{wszystkieTabGr[id]};
    int sumaPunktow = 0;
    std::string ponownaProba {"T"};
    int dozwolonePoejdscia = 2;

    while (sumaPunktow < 30 and toupper(ponownaProba[0]) == 'T') {
        dozwolonePoejdscia--;
        sumaPunktow = 0;
        pierwszeRuchPlansza.kolejGracza(0, nrRundy);

        for (auto ciag: pierwszeRuchPlansza.wszystkieCiagi) {
            for (auto zetony: ciag->ciagZetonow) {
                Zeton* pZ = &(*zetony);
                sumaPunktow += *pZ;
            }
        }

        if (pierwszeRuchPlansza.poprawnePierwszewylozenie) {
            if (sumaPunktow < 30 and dozwolonePoejdscia > 0) {
                std::cout << "Wylozenie mialo wartosc ponizej 30 lub bylo niepoprawne. Czy chcesz sprobowac jeszcze raz? [T] - tak (dozwolona 1 ponowna proba)\n";
                std::getline(std::cin, ponownaProba);
                if (toupper(ponownaProba[0]) == 'T') pierwszeRuchPlansza = {wszystkieTabGr[id]};
            } else ponownaProba = 'N';
        } else ponownaProba = 'N';
    }

    if (pierwszeRuchPlansza.poprawnePierwszewylozenie and sumaPunktow >= 30) {
        std::cout << "~~Poprawne pierwsze wylozenie~~\n";

        for (auto ciag: pierwszeRuchPlansza.wszystkieCiagi) {
            wszystkieCiagi.push_back(new CiagZetonow(*ciag));
        }
        wszystkieTabGr[id] = new TabliczkaGracza(*pierwszeRuchPlansza.wszystkieTabGr[0]);
        wszystkieTabGr[id]->nrGracza = id + 1;

        if (!pierwszeRuchPlansza.tabelaZwyciezcow.empty()) {
            tabelaZwyciezcow.push_back(nrRundy);
            tabelaZwyciezcow.push_back(id + 1);
        }

    } else {
        if (pierwszeRuchPlansza.tabelaZwyciezcow.empty()) {

            if (resztaZetonowWWorku.empty()) dodatkoweZetony();

            std::cout << "Wylozenie jest niepoprawne! Ciagniesz zeton z worka! -->";
            resztaZetonowWWorku.back()->pokazZeton();
            std::cout << "\n";

            wszystkieTabGr[id]->tabliczka.push_back(resztaZetonowWWorku.back());
            resztaZetonowWWorku.pop_back();
            wszystkieTabGr[id]->tabliczka.sort([](Zeton *a, Zeton *b) { return *a < *b; });

            wszystkieTabGr[id]->pierszyRuch = true;
            czyWygranaWlakowerem(id, nrRundy);
        } else {
            wszystkieTabGr[id]->pierszyRuch = true;
            wszystkieTabGr[id]->skonczyl = true;
            tabelaZwyciezcow.push_back(-27); //byle ujemne
            tabelaZwyciezcow.push_back(id + 1);
        }
    }

}

std::pair<int, int> Plansza::sprKomendyPodzielCiag(const std::string &komenda) {

    std::pair<int, int> wynik{0, 0};
    std::string ciag;
    std::string nrZetonu;
    bool jeszczeCiag = true;

    for (int i = 1; i < komenda.size(); i++) { // P11-12 "P" z przodu nas nie interesuje
        if (komenda[i] == '-') jeszczeCiag = false;
        else if (jeszczeCiag) ciag.push_back(komenda[i]);
        else nrZetonu.push_back(komenda[i]);
    }

    if (!ciag.empty() and !nrZetonu.empty()) {
        for (auto c: ciag) {
            if (c < 48 or c > 57) return wynik;
        }
        for (auto c: nrZetonu) {
            if (c < 48 or c > 57) return wynik;
        }
        wynik = {stoi(ciag), stoi(nrZetonu)};
    }

    return wynik;
}

void Plansza::polaczCiagi(int idPierwszego, int idDrugiego) {
    if (!wszystkieCiagi[idDrugiego]->ciagZetonow.empty()) {
        wszystkieCiagi[idPierwszego]->ciagZetonow.merge(wszystkieCiagi[idDrugiego]->ciagZetonow);
        delete wszystkieCiagi[idDrugiego];
        wszystkieCiagi.erase(wszystkieCiagi.begin() + idDrugiego);
    }

}

bool Plansza::bylZTabGr(Zeton *ze, const int &idGr) {
    bool wynik = false;

    for (auto z: kopiaZaposwaPlanszy->wszystkieTabGr[idGr]->tabliczka) {
        if (ze->idZetonu == z->idZetonu) {
            wynik = true;
            break;
        }
    }

    return wynik;
}

void Plansza::sprOgolnejPoprawnosciKomendy(const int &id, const std::string &komenda, bool &koniecTury, const int nrRundy) {

    if (komenda == "surr" or komenda == "SURR") {
        wszystkieTabGr[id]->skonczyl = true;
        tabelaZwyciezcow.push_back(-27);
        tabelaZwyciezcow.push_back(id + 1);
        pierwszeWykonanieKomendy = false;
        koniecTury = true;
        if (wszystkieTabGr.size() == 1) //czyli jest pierwsze wyłożenie
            poprawnePierwszewylozenie = false;
    } else {
        if ((4 > komenda.size() and komenda.size() > 1) or komenda.size() > 6) {
            std::cout << "Wprowadzono niepoprawna komende! Wprowadz poprawna. W razie trudnosci wpisz litere h.\n";
            pierwszeWykonanieKomendy = false;


        } else if (komenda.size() == 1) {

            if (komenda[0] == 'H' or komenda[0] == 'h') Menu::wyswietlSterowanie();
            else if (komenda[0] == 'R' or komenda[0] == 'r') Menu::wyswietlZasady();
            else if (komenda[0] == 'S' or komenda[0] == 's') pokazPlansze();
            else if (komenda[0] == 'F' or komenda[0] == 'f') {
                if (koncoweSprawdzanieRuchu(id)) {
                    koniecTury = true;
                    if (wszystkieTabGr.size() == 1) //czyli jest pierwsze wyłożenie
                        poprawnePierwszewylozenie = true;
                    if (czySkonczyl(id, nrRundy)) std::cout << "\nGratulacje ukonczyles rozgrywke!\n";

                } else {
                    if (wszystkieTabGr.size() != 1) { //czyli NIE jest pierwsze wyłożenie

                        if (resztaZetonowWWorku.empty()) dodatkoweZetony();

                        std::cout << "Wylozenie jest niepoprawne! Ciagniesz zeton z worka! -->";
                        resztaZetonowWWorku.back()->pokazZeton();
                        std::cout << "\n";

                        *this = *kopiaZaposwaPlanszy;

                        wszystkieTabGr[id]->tabliczka.push_back(resztaZetonowWWorku.back());
                        resztaZetonowWWorku.pop_back();
                        wszystkieTabGr[id]->tabliczka.sort([](Zeton *a, Zeton *b) { return *a < *b; });


                        czyWygranaWlakowerem(id, nrRundy);
                    } else poprawnePierwszewylozenie = false;

                    koniecTury = true;

                }

            } else
                std::cout
                        << "Wprowadzono niepoprawna komende! Wprowadz poprawna. W razie trudnosci wpisz litere h.\n";
            pierwszeWykonanieKomendy = false;
        }
    }
}

void Plansza::KomendaDziel(const std::string &komenda) {
    if (komenda[0] == 'D' or
        komenda[0] == 'd') { //komenda np. D7-3, d11-12 // ciągi wyświetlane są od 1
        std::pair<int, int> daneZKomendy = sprKomendyPodzielCiag(komenda);
        if (daneZKomendy.first == 0 or daneZKomendy.first > wszystkieCiagi.size() or
            daneZKomendy.second > wszystkieCiagi[daneZKomendy.first - 1]->ciagZetonow.size()) {
            std::cout
                    << "Wprowadzono niepoprawna komende! Wprowadz poprawna. W razie trudnosci wpisz litere h.\n";
        } else
            wszystkieCiagi.push_back(podzielCiagi(wszystkieCiagi[daneZKomendy.first - 1], daneZKomendy.second));

        pierwszeWykonanieKomendy = false;
    }
}

void Plansza::KomendaLacz(const std::string &komenda) {
    if (komenda[0] == 'M' or komenda[0] == 'm') { //Łaczenie l11-2 l1-3
        std::pair<int, int> daneZKomendy = sprKomendyPodzielCiag(komenda); //sprKPodzielC zadzaiła jak należy
        if (daneZKomendy.first > wszystkieCiagi.size() or daneZKomendy.second > wszystkieCiagi.size()) {
            std::cout
                    << "Wprowadzono niepoprawna komende! Wprowadz poprawna. W razie trudnosci wpisz litere h.\n";
        } else polaczCiagi(daneZKomendy.first - 1, daneZKomendy.second - 1);

        pierwszeWykonanieKomendy = false;
    }
}

void Plansza::KomendaNowy(std::string &komenda, int id) {
    if (komenda[0] == 'N' or komenda[0] == 'n') {  // N-11C
        komenda.replace(komenda.begin(), komenda.begin() + 1, "1",
                        1); //zamieniamy N na 1 tak, żeby użyć już napisanej funkcji pod ruch gracza
        std::pair<int, std::list<Zeton *>::iterator> nrCiaguIter = wszystkieTabGr[id]->jestZetonWTab(komenda);
        if (!nrCiaguIter.first)
            std::cout
                    << "Nie posiadasz takiego Zetonu lub komenda jest niepoprawna! Wprowadz poprawna komende. W razie trudnosci wpisz litere h.\n";
        else {
            wszystkieCiagi.push_back(new CiagZetonow);
            ruchGracza(id, wszystkieCiagi.size(), nrCiaguIter.second);
        }
        pierwszeWykonanieKomendy = false;
    }
}

void Plansza::KomendaWez(const std::string &komenda, int id) {
    if (komenda[0] == 'T' or komenda[0] == 't') { //t1-2
        std::pair<int, int> daneZKomendy = sprKomendyPodzielCiag(komenda);
        if (daneZKomendy.second == 0 or daneZKomendy.first > wszystkieCiagi.size() or
            daneZKomendy.second > wszystkieCiagi[daneZKomendy.first - 1]->ciagZetonow.size()) {
            std::cout
                    << "Wprowadzono niepoprawna komende! Wprowadz poprawna. W razie trudnosci wpisz litere h.\n";
        } else {
            auto iterZeton = wszystkieCiagi[daneZKomendy.first - 1]->dajIterZeton(daneZKomendy.second);
            Zeton *ze = *iterZeton;
            if (bylZTabGr(ze, id)) {
                wszystkieTabGr[id]->tabliczka.push_back(*iterZeton);
                wszystkieCiagi[daneZKomendy.first - 1]->ciagZetonow.erase(iterZeton);
            } else {
                wszystkieTabGr[id]->podreczneZetony.push_back(*iterZeton);
                wszystkieCiagi[daneZKomendy.first - 1]->ciagZetonow.erase(iterZeton);
            }
        }
        pierwszeWykonanieKomendy = false;
    }
}

void Plansza::KomendaRuch(const std::string &komenda, int id) {

    std::pair<int, std::list<Zeton *>::iterator> nrCiaguIter = wszystkieTabGr[id]->jestZetonWTab(komenda);
    if (nrCiaguIter.first > wszystkieCiagi.size() or !nrCiaguIter.first)
        std::cout
                << "Nie posiadasz takiego Zetonu lub komenda jest niepoprawna! Wprowadz poprawna komende. W razie trudnosci wpisz litere h.\n";
    else ruchGracza(id, nrCiaguIter.first, nrCiaguIter.second);

    pierwszeWykonanieKomendy = false;
}

bool Plansza::koncoweSprawdzanieRuchu(const int &id) {
    bool poprawnyRuch = true;

    if (kopiaZaposwaPlanszy->wszystkieTabGr[id]->tabliczka.size() <= wszystkieTabGr[id]->tabliczka.size() or
        !wszystkieTabGr[id]->podreczneZetony.empty()) {
        poprawnyRuch = false;

    } else {
        for (auto ciag: wszystkieCiagi) {
            if (!ciag->ciagZetonow.empty()) { //jak pusty to ignorujemy lecimy dalej
                if (ciag->ciagZetonow.size() < 3) {
                    poprawnyRuch = false;
                    break;

                } else if (!ciag->poprawnoscCiagu()) {
                    poprawnyRuch = false;
                    break;
                }
            }
        }
    }

    return poprawnyRuch;
}

void Plansza::dodatkoweZetony() {
    static int idZaposwychZetonow = 270; //orginały mają id do 100 coś, więc po prostu więcej
    for (int i = 0; i < 2; i++) {
        for (int cyfraZetonu = 1; cyfraZetonu <= 13; cyfraZetonu++) {
            resztaZetonowWWorku.push_back(new ZetonCyfra{idZaposwychZetonow++, cyfraZetonu, 'R'});
            resztaZetonowWWorku.push_back(new ZetonCyfra{idZaposwychZetonow++, cyfraZetonu, 'G'});
            resztaZetonowWWorku.push_back(new ZetonCyfra{idZaposwychZetonow++, cyfraZetonu, 'B'});
            resztaZetonowWWorku.push_back(new ZetonCyfra{idZaposwychZetonow++, cyfraZetonu, 'Y'});
        }
        resztaZetonowWWorku.push_back(new Joker{idZaposwychZetonow++});
    }
}


/////////////////////


void Plansza::testkopi() {
    if (kopiaZaposwaPlanszy) {
        int j = 1;

        std::cout << "TEST KOPIA:" << std::string(27, '~') << "\n";
        for (auto ciagi: kopiaZaposwaPlanszy->wszystkieCiagi) {
            std::cout << "-(" << j++ << ")-";
            ciagi->pokazCiag();
        }
        std::cout << std::string(27, '~') << "\n" << "Tabliczki graczy:\n";

        for (auto tabGr: kopiaZaposwaPlanszy->wszystkieTabGr)
            tabGr->pokazTabliczke();
        std::cout << std::string(27, '~') << "\n";
        std::cout << "KOPIA: ";
        for (auto resztaWworku: kopiaZaposwaPlanszy->resztaZetonowWWorku) {
            resztaWworku->pokazZeton();
        }
        std::cout << "\nORGNL: ";
        for (auto resztaWworku: resztaZetonowWWorku) {
            resztaWworku->pokazZeton();
        }
    }
}

void Plansza::testKolejGracza(int id, std::vector<std::string> komendy) {
    kopiaZaposwaPlanszy = new Plansza(*this);
    bool koniecTury = false;

    std::cout << "Ruch gracza nr " << wszystkieTabGr[id]->nrGracza
              << "\n"; //k - koniec tury, h przypomnienie sterowania
    if (wszystkieTabGr[id]->pierszyRuch) std::cout << "Pierwsze wylozenie musi miec wspolna wartosc zetonow >=30";
    std::string komenda;

    for (int i = 0; i < komendy.size(); i++) {
        komenda = komendy[i];
        std::cout << komenda << std::endl;
        //po wykryciu, że dana komenda ma być wykonana, metoda ją wykonuje i zmienia pierwszeWykonanieKomendy na false
        sprOgolnejPoprawnosciKomendy(id, komenda, koniecTury, 0);
        if (pierwszeWykonanieKomendy) {
            KomendaDziel(komenda);
            if (pierwszeWykonanieKomendy) {
                KomendaLacz(komenda);
                if (pierwszeWykonanieKomendy) {
                    KomendaNowy(komenda, id);
                    if (pierwszeWykonanieKomendy) {
                        KomendaWez(komenda, id);
                        if (pierwszeWykonanieKomendy) {
                            KomendaRuch(komenda, id);
                        }
                    }
                }
            }
        }

        pierwszeWykonanieKomendy = true;
    }
    delete kopiaZaposwaPlanszy;
    kopiaZaposwaPlanszy = nullptr;
}

void Plansza::testWieleKomend () {
    std::string komenda;
    std::vector<std::string> wynik;
    std::string pojedynczaKomenda;
    std::cout << "testWieluKomend\n";
    std::getline(std::cin, komenda);
    komenda.push_back(';');

    for (auto c : komenda) {
        switch (c) {
            case ';':
                wynik.push_back(pojedynczaKomenda);
                pojedynczaKomenda = "";
                break;
            default:
                pojedynczaKomenda.push_back(c);
        }
    }
    std::cout <<"Vc:";
    for (auto s : wynik) {
        std::cout << s << " ";
    }

}
