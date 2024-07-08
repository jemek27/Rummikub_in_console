//
// Created by jemek on 21.04.2023.
//
#include <list>
#include "Zeton.h"
#include "ZetonCyfra.h"

#ifndef RUMMIKUB_CIAGZETONOW_H
#define RUMMIKUB_CIAGZETONOW_H

class CiagZetonow {
    friend class Plansza;
    std::list<Zeton*> ciagZetonow;
public:
    CiagZetonow() : ciagZetonow() {};
    CiagZetonow(CiagZetonow &inny);
    ~CiagZetonow();

    void pokazCiag ();
    bool poprawnoscCiagu();

    std::list<Zeton *>::iterator dajIterZeton (int n);

    void testPoprawnoscCiagu ();
//    void polaczCiagi (CiagZetonow drugi);
//    void testPolacz ();
//    void testPodziel ();
};


#endif //RUMMIKUB_CIAGZETONOW_H
