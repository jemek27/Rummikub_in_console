//
// Created by jemek on 21.04.2023.
//
#include "Zeton.h"
#include "WorekNaZetony.h"
#include <list>
#include <cctype>
#include <windows.h>
#include <sstream>

#ifndef RUMMIKUB_TABLICZKAGRACZA_H
#define RUMMIKUB_TABLICZKAGRACZA_H


class TabliczkaGracza {
    friend class Plansza;
    std::list<Zeton*> tabliczka;
    std::list<Zeton*> podreczneZetony;
    std::string nazwaGracza;
    int nrGracza;
    bool pierszyRuch;
    bool skonczyl;
public:
    TabliczkaGracza(WorekNaZetony & worek, int nrG);
    TabliczkaGracza(WorekNaZetony & worek, int nrG, const std::string& nazwa);
    TabliczkaGracza(TabliczkaGracza &inna);
    ~TabliczkaGracza();
    void pokazTabliczke ();
    std::pair<int, std::list<Zeton*>::iterator> jestZetonWTab(const std::string& komenda);
};


#endif //RUMMIKUB_TABLICZKAGRACZA_H
