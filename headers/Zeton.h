//
// Created by jemek on 21.04.2023.
//
#include <iostream>

#ifndef RUMMIKUB_ZETON_H
#define RUMMIKUB_ZETON_H

class Zeton {
public:
    int cyfra;
    char kolor; //Y = żółty, B = niebieski, G = zielony, R = czerwony
    const int idZetonu;

    Zeton(int id, int c, char k) : cyfra(c), kolor(k), idZetonu(id) {};
    virtual ~Zeton() = default;

    virtual void    pokazZeton () = 0;
    virtual int     dajWartosc () = 0; //potrzebane, żeby od JK dawało tempWartość
    virtual char    dajKolor () = 0;
    virtual bool    nadajWartosciZetonowe (int i, char c) = 0;

    virtual void display(std::ostream& os) const;
    virtual void read(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Zeton& zeton);

    friend std::istream& operator>>(std::istream& is, Zeton& zeton);

    virtual operator int() = 0;

};








#endif //RUMMIKUB_ZETON_H
