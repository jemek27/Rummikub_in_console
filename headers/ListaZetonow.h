//
// Created by jemek on 15.06.2023.
//
#include <ostream>
#include "ElementListy.h"
#include "ZetonCyfra.h" // potrzebne tylko do metody test

#ifndef RUMMIKUB_LISTAZETONOW_H
#define RUMMIKUB_LISTAZETONOW_H

// lista zaimplementowana tylko na poczet wymagań projektowych
class ListaZetonow {
    ElementListy* pierwszy;

public:
    ListaZetonow() : pierwszy(nullptr) {};

    void wyswietlListe();
    void dodajZeton(Zeton* zeton);
    void usunElement(Zeton* zeton);
    void polonczListy(const ListaZetonow& lista);
    ListaZetonow podzielListy(int indeks);

    class Iterator {
    private:
        ElementListy* aktualny;

    public:
        Iterator(ElementListy* elem);

        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        Zeton* operator*() const;
    };

    Iterator begin() const;
    Iterator end() const;

    static void testListy();
};


#endif //RUMMIKUB_LISTAZETONOW_H
