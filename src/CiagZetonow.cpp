//
// Created by jemek on 21.04.2023.
//

#include "../headers/CiagZetonow.h"


void CiagZetonow::pokazCiag() {
    for (auto z: ciagZetonow) z->pokazZeton();
    std::cout << "\n";
}

CiagZetonow::~CiagZetonow() {
    for (auto zP: ciagZetonow) delete zP;
}

std::list<Zeton *>::iterator CiagZetonow::dajIterZeton(int n) {
    auto iter = ciagZetonow.begin();
    std::advance(iter, n - 1);
    return iter;
}

CiagZetonow::CiagZetonow(CiagZetonow &inny) {
    for (auto pZ: inny.ciagZetonow) {
        if (pZ->cyfra != 0) { //jeśli to JK to mamy 0
            ciagZetonow.push_back(new ZetonCyfra(pZ->idZetonu, pZ->cyfra, pZ->kolor));
        } else
            ciagZetonow.push_back(new Joker(pZ->dajWartosc(), pZ->dajKolor(), pZ->idZetonu));
    }
}

bool CiagZetonow::poprawnoscCiagu() { //Na podstawie 2 pierwszych żetonów sprawdzamy, czy mam do czynienia z tzw. grupa 7C 7P 7N lub serią 2C 3C 4C
    if (!ciagZetonow.empty()) {
        ciagZetonow.sort([](Zeton *a, Zeton *b) { return *a < *b; });
        std::list<Zeton *>::iterator iterZeton = ciagZetonow.begin();

        int wartoscPierwszegoZetonu = (*iterZeton)->dajWartosc();
        char kolorPierwszegoZetonu = (*iterZeton)->dajKolor();
        std::advance(iterZeton, 1);
        int wartoscDrugiegoZetonu = (*iterZeton)->dajWartosc();


        if (wartoscPierwszegoZetonu == wartoscDrugiegoZetonu) { //spr dla grupy
            std::string jakieBylyKolory;

            for (auto zeton: ciagZetonow) {

                for (auto kolor: jakieBylyKolory) {
                    if (kolor == zeton->dajKolor()) return false;
                }
                jakieBylyKolory.push_back(zeton->dajKolor());

                if (wartoscPierwszegoZetonu != zeton->dajWartosc()) return false;
            }

        } else if (wartoscPierwszegoZetonu + 1 == wartoscDrugiegoZetonu) {
            int wartoscPoprzedniegoZetunu = wartoscPierwszegoZetonu - 1; //żeby dla pierwszego żetonu działało

            for (auto zeton: ciagZetonow) {
                if (zeton->dajKolor() != kolorPierwszegoZetonu or
                    zeton->dajWartosc() != wartoscPoprzedniegoZetunu + 1)
                    return false;

                wartoscPoprzedniegoZetunu = zeton->dajWartosc();
            }

        } else { return false; }
    }
    return true;
}


//////////////////////////////////


/*
void CiagZetonow::polaczCiagi(CiagZetonow drugi) {
    ciagZetonow.merge(drugi.ciagZetonow);
}
 */
/*
void CiagZetonow::testPolacz() {
    CiagZetonow a, b;
    auto z1 = new ZetonCyfra{1,'C'};
    auto z2 = new ZetonCyfra{2,'C'};
    auto z3 = new ZetonCyfra{3,'C'};
    auto z4 = new ZetonCyfra{4,'C'};
    auto z11 = new ZetonCyfra{1,'C'};
    auto z22 = new ZetonCyfra{2,'C'};
    auto z33 = new ZetonCyfra{3,'Z'};
    auto z44 = new ZetonCyfra{4,'Z'};
    a.ciagZetonow.push_back(z1);
    a.ciagZetonow.push_back(z2);
    a.ciagZetonow.push_back(z3);
    a.ciagZetonow.push_back(z4);
    b.ciagZetonow.push_back(z11);
    b.ciagZetonow.push_back(z22);
    b.ciagZetonow.push_back(z33);
    b.ciagZetonow.push_back(z44);
    std::cout << "\nA:";
    a.pokazCiag();
    std::cout << "\nb:";
    b.pokazCiag();
    a.polaczCiagi(b);
    std::cout << "\nA:";
    a.pokazCiag();
    std::cout << "\nb:";
    b.pokazCiag();
}
*/


/*
void CiagZetonow::testPodziel() {
    std::cout << "Test PodzielCiag\n";
    for (int cyfraZetonu = 1; cyfraZetonu <= 13; cyfraZetonu++) {
        ciagZetonow.push_back(new ZetonCyfra{cyfraZetonu, 'C'});
    }
    std::list<Zeton*> drugi;
    int gdzie = 3;
    int tempgdzie = gdzie;
    int poczatkowyRozmiar = ciagZetonow.size();
    int licznik = 0;
    auto iter =  ciagZetonow.begin();

    while (tempgdzie--) iter++;
    std::copy(iter, ciagZetonow.end(), std::back_inserter(drugi));
    while (poczatkowyRozmiar - gdzie > licznik) {
        licznik++;
        ciagZetonow.pop_back();
    }

    std::cout << "1\n";
    for (auto a : ciagZetonow)
        a->pokazZeton();
    std::cout << "2\n";
    for (auto a : drugi)
        a->pokazZeton();
}
*/

void CiagZetonow::testPoprawnoscCiagu() {

    std::cout << "\n\n~~~~testPoprawnoscCiagu~~~~\n\n";

    std::string CNZP {"CNZP"};
    auto c1 = new CiagZetonow;
    for (int cyfraZetonu = 6; cyfraZetonu <= 13; cyfraZetonu++)
        c1->ciagZetonow.push_back(new ZetonCyfra{0,cyfraZetonu, 'C'});

    auto c2 = new CiagZetonow;
    for (auto c : CNZP)
        c2->ciagZetonow.push_back(new ZetonCyfra{0,7, c});

    if (c1->poprawnoscCiagu()) std::cout << __LINE__ << " C1 jest poprawne - ok\n";
    if (c2->poprawnoscCiagu()) std::cout << __LINE__ << " C2 jest poprawne - ok\n";

    auto jk = new Joker;
    jk->nadajWartosciZetonowe(5, 'C');

    c1->ciagZetonow.push_back(jk);
    c2->ciagZetonow.push_back(jk);

    if (c1->poprawnoscCiagu()) std::cout << __LINE__ << " C1 jest poprawne - ok\n";
    if (c2->poprawnoscCiagu()) std::cout << __LINE__ << " C1 jest poprawne - nie ok\n";

    c1->ciagZetonow.push_back(new ZetonCyfra{0,3, 'C'});

    if (c1->poprawnoscCiagu()) std::cout << __LINE__ << " C1 jest poprawne - nie ok\n";

}