//
// Created by jemek on 21.04.2023.
//

#ifndef RUMMIKUB_JOKER_H
#define RUMMIKUB_JOKER_H


#include "Zeton.h"
#include <cctype>
#include <windows.h>

class Joker : public Zeton{
    int tempCyfra;
    char tempKolor;
public:
    Joker(int id = 0) : Zeton{id, 0, '0' }, tempCyfra(27), tempKolor('V') {};
    Joker(int tempC, char tempK, int id) : Zeton{id, 0, '0' }, tempCyfra(tempC), tempKolor(tempK) {};
    ~Joker() override = default;

    void pokazZeton () override;
    bool nadajWartosciZetonowe (int i, char c) override;
    int dajWartosc () override;
    char dajKolor () override; 


    bool operator==(Zeton &inny);
    bool operator<(Zeton &inny);
    operator int();

    void display(std::ostream& os) const override;
    void read(std::istream& is) override;

};


#endif //RUMMIKUB_JOKER_H
