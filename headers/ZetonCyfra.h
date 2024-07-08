//
// Created by jemek on 21.04.2023.
//

#ifndef RUMMIKUB_ZETONCYFRA_H
#define RUMMIKUB_ZETONCYFRA_H

#include <iostream>
#include "Zeton.h"
#include "Joker.h"
#include <windows.h>

class ZetonCyfra : public Zeton{
public:
    ZetonCyfra(int id, int c, char k) : Zeton(id, c, k) {};
//    ZetonCyfra(std::istream& is) ;
    ~ZetonCyfra() override = default;

    void pokazZeton () override;
    int dajWartosc () override;
    char dajKolor () override;
    bool nadajWartosciZetonowe (int i, char c); //to musi być inaczej nie działa

    ZetonCyfra &operator+(int n);
    bool operator==(ZetonCyfra &inny);
    bool operator<(ZetonCyfra &inny);
    bool operator==(Joker &joker);
    bool operator<(Joker &joker);
    operator int();

    void display(std::ostream& os) const override;
    void read(std::istream& is) override;
    /*
    friend std::ostream& operator<<(std::ostream& os, const Zeton& zeton);
    friend std::istream& operator>>(std::istream& is, Zeton& zeton);
*/
};


#endif //RUMMIKUB_ZETONCYFRA_H
