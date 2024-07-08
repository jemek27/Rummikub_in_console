//
// Created by jemek on 16.06.2023.
//
#include "../headers/testowanie.h"

void testowanie1 () {
    /*
    ListaZetonow test;
    test.testListy();

 //zabawa kolorami
 HANDLE  hConsole;
 int k;

 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

 for(k = 1; k < 255; k++)
 {
     // pick the colorattribute k you want
     SetConsoleTextAttribute(hConsole, k);
     std::cout << k << " I want to be nice today!" << std::endl;
 }

 std::cin.get();



    WorekNaZetony worekTest{5};

    worekTest.test();

    ZetonCyfra z1{1, 'Y'};
    ZetonCyfra z2{1, 'Y'};
    ZetonCyfra z3{2, 'Y'};
    ZetonCyfra z4{2, 'R'};
    Joker j{};
    j.nadajWartosciZetonowe(2, 'R');
    Zeton *pz1, *pz2;




    if (z1 == z2) std::cout << "12 rowne - ok\n";
    if (z1 == z3) std::cout << "13rowne - NIE ok\n";
    if (z3 == z4) std::cout << "34rowne - NIE ok\n";
    if (z4 == j)  std::cout << "4jrowne - ok\n";
    j.nadajWartosciZetonowe(7, 'R');
    if (z4 == j)  std::cout << "4jrowne - NIE ok\n";


    std::cout << "Test tabGr:\n";
    TabliczkaGracza tG1{worekTest, 1};
    TabliczkaGracza tG2{worekTest, 2};

    tG1.pokazTabliczke();
    tG2.pokazTabliczke();
    worekTest.test();

    std::cout << "Test Z+1:\n";
    if (z1 + 1 == z3) std::cout << "(Z1+1)Z3rowne - ok\n";
    if (z4 + 1 == j)  std::cout << "(Z4+1)jrowne - nie ok\n";



    auto testCiag = new CiagZetonow;
//    testCiag->testPodziel();
//    testCiag->testPolacz();

*/
    /*
    std::vector<CiagZetonow*> wszystkieCiagi;
    auto a = new CiagZetonow;
    auto b = new CiagZetonow;
    auto z1 = new ZetonCyfra{1,'C'};
    auto z2 = new ZetonCyfra{2,'C'};
    auto z3 = new ZetonCyfra{3,'C'};
    auto z4 = new ZetonCyfra{4,'C'};
    auto z11 = new ZetonCyfra{1,'C'};
    auto z22 = new ZetonCyfra{2,'C'};
    auto z33 = new ZetonCyfra{3,'Z'};
    auto z44 = new ZetonCyfra{4,'Z'};
*/
/*
    std::cout << __LINE__ << std::endl;
    lista.polonczListy(lista2);
    lista.wyslietl();
    std::cout << __LINE__ << std::endl;
    lista2.wyslietl();
    ListaZetonow lista3 = lista.podzielListy(4);
    std::cout << __LINE__ << std::endl;
    lista.wyslietl();
    std::cout << __LINE__ << std::endl;
    lista3.wyswietlListe();

//    a->ciagZetonow.push_back(z1);
//    a->ciagZetonow.push_back(z2);
//    a->ciagZetonow.push_back(z3);
//    a->ciagZetonow.push_back(z4);
//    b->ciagZetonow.push_back(z11);
//    b->ciagZetonow.push_back(z22);
//    b->ciagZetonow.push_back(z33);
//    b->ciagZetonow.push_back(z44);
    wszystkieCiagi.push_back(a);
    wszystkieCiagi.push_back(b);
    std::cout << "rozmiar:" << wszystkieCiagi.size();
    delete a;
    wszystkieCiagi.erase(wszystkieCiagi.begin());
    std::cout << "rozmiar:" << wszystkieCiagi.size();
    */
/*
    std::string aa = "abcd";
    aa.replace(aa.begin(), aa.begin()+1, '1', 1);
    std::cout << aa;
    std::list<int> testlisty;
    for (auto iter = testlisty.begin(); iter != testlisty.end(); iter++)
        std::cout << *iter;
*/

/*
    ZetonCyfra zC1 {1,'Y'};
    int testInt = 2;
    testInt += zC1;
    std::cout << testInt << "\n";
    testInt += j;
    std::cout << "Spodziewane 10, wynik:" << testInt << "\n";
//test poprawności komend



*/
}

void odczytZapis () {
    OdczytZapisyDoPliku handler;

    // Zapisywanie pojedynczych wierszy
    std::vector<std::string> row1 = {"string1", "string2", "string3"};
    std::vector<std::string> row2 = {"innystring1", "innystring2"};
    std::vector<std::string> row3 = {"string1v2", "string2v2", "string3v2", "string4v2"};

    const std::string filename = "dane.txt";
    handler.zapisTabZwy(row1, filename);
    handler.zapisTabZwy(row2, filename);
    handler.zapisTabZwy(row3, filename);

    // Odczytywanie wszystkich wierszy z pliku
    std::vector<std::vector<std::string>> loadedData = handler.odczytWszystkichTabZwy(filename);

    // Wyświetlanie załadowanych danych
    for (const auto& row : loadedData) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

void kolory(){
    HANDLE  hConsole;
    int k;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(k = 1; k < 255; k++)
    {
// pick the colorattribute k you want
        SetConsoleTextAttribute(hConsole, k);
        std::cout << k << " I want to be nice today!" << std::endl;
    }

    std::cin.get();
}


void testOperatoryStrumieniowe(){



    auto z1 = new ZetonCyfra(1, 4, 'G');
    auto z2 = new ZetonCyfra(2, 5, 'G');
    auto z3 = new ZetonCyfra(3, 6, 'G');
    std::cout << "Z1 Z2 Z3:" << *z1 << " " <<  *z2 << " "  << *z3 << std::endl;

    Zeton* p1 = z1;
    Zeton* p2 = z2;
    Zeton* p3 = z3;
    std::cout << "p1 p2 p3:" << (*p1) << " " <<  *p2 << " " << *p3 << std::endl;

    auto j1 = new Joker(0);
    auto j2 = new Joker(7, 'G', 2);;

    p1 = j1;
    p2 = j2;

    std::cout << "p1 p2 p3:" << (*p1) << " " <<  *p2 << " " << *p3 << std::endl;

//    std::cin >> *p1;
//    std::cout << "p1 po cin" << (*p1);
}

void testRozgrywki (){
    std::cout << "\nTEST KOMEND\n\n";
    WorekNaZetony worekNiePomieszany {3};
    std::vector<Zeton*> vectorZetonow;
    int licznik = 0;
    for (int cyfraZetonu = 1; cyfraZetonu <= 13; cyfraZetonu++) {
//        vectorZetonow.push_back(new ZetonCyfra{cyfraZetonu, 'C', licznik++});
        vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'Y'});
        vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'B'});
        vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'G'});
        vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'R'});
        vectorZetonow.push_back(new Joker(licznik++));
    }

    worekNiePomieszany.vectorZetonow = vectorZetonow;
//    worekNiePomieszany.test();

    std::vector<std::string> komendy {"1-11c", "n-12c", "1-10p", "1-13p", "s", "c1-2", "s", "d1-1", "s", "t1-1", "f"};
    std::vector<std::string> komendy2 {"t2-1", "s", "f"};

//    Plansza planszaTestKomend {worekNiePomieszany, 3};

//    while (true)
//        for (int i = 0; i < 2; i++) {
//            planszaTestKomend.pokazPlansze();
//            planszaTestKomend.kolejGracza(i);
//
//        }

    Menu testMenu;

    while (testMenu.rozgrywka) {
        int licznikTur = 0;
        testMenu.rundaTrwa = true;
////////
        std::vector<Zeton*> vectorZetonow;
        int licznik = 0;
        for (int cyfraZetonu = 1; cyfraZetonu <= 13; cyfraZetonu++) {
//        vectorZetonow.push_back(new ZetonCyfra{cyfraZetonu, 'C', licznik++});
            vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'Y'});
            vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'B'});
            vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'G'});
            vectorZetonow.push_back(new ZetonCyfra{licznik++, cyfraZetonu, 'R'});
            vectorZetonow.push_back(new Joker(licznik++));
        }

        worekNiePomieszany.vectorZetonow = vectorZetonow;
//////////////
        if (testMenu.przywitanie()) {
            std::vector<std::string> gracze = testMenu.iloscGraczy();
            int  ileGR = gracze.size();
//          WorekNaZetony testWorekNaZetony(ileGR);
            Plansza testPlasza(worekNiePomieszany, gracze);
            while (testMenu.rundaTrwa) { // do testu  and licznikTur != 2
                if (licznikTur++ == 0) testMenu.wyswietlSterowanie();

                for (int i = 0; i < ileGR; i++) {
                    testPlasza.kolejGracza(i, licznikTur);
                }
                if (testPlasza.iluSkonczylo() >= ileGR - 1 ) testMenu.rundaTrwa = false;
            }
            testMenu.wypiszTabZwyciezcow(testPlasza.dajTabZwy(), gracze);
        }
        vectorZetonow.clear();
    }

/*
    Menu testKomendMenu;
//    planszaTestKomend.testWieleKomend();
    testKomendMenu.rozgrywka = true;
    int ktoraKoleja11 = 0;

    while (testKomendMenu.rozgrywka) {
        ktoraKoleja11++;

        for (int i = 0; i < 3; i++) {
            planszaTestKomend.kolejGracza(i, ktoraKoleja11);
        }
        if (planszaTestKomend.iluSkonczylo() == 3 - 1 or planszaTestKomend.iluSkonczylo() == 3) testKomendMenu.rozgrywka = false;
    }
    testKomendMenu.wypiszTabZwyciezcow(planszaTestKomend.dajTabZwy());
//    planszaTestKomend.testKolejGracza(0, komendy);
//    planszaTestKomend.testKolejGracza(1, komendy2);




    std::cout << "\nTEST KOMEND\n\n";

    CiagZetonow c1;
    c1.testPoprawnoscCiagu();
    */
/*
    //test ruchgracza
    WorekNaZetony worek{2};
    Plansza plansza{worek, 2};
    plansza.pokazPlansze();
    bool nieKoniec = true;
    int ktoraKoleja = 0;

    while (nieKoniec) {
        ktoraKoleja++;

        for (int i = 0; i < 2; i++) {
            plansza.kolejGracza(i, ktoraKoleja);
            plansza.pokazPlansze();
        }
        if (plansza.iluSkonczylo() == 2 - 1 ) nieKoniec = false;
    }
    std::cout << "\n\nKONIECCCCCCCCCCCCCCCCCCCCC\n\n";
    */
}
