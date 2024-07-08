//
// Created by jemek on 15.06.2023.
//

#include "../headers/ListaZetonow.h"

void ListaZetonow::wyswietlListe() {

   if (pierwszy == nullptr) {
       std::cout << "Lista jest pusta." << std::endl;
   } else {
       ElementListy* aktualny = pierwszy;
       while (aktualny != nullptr) {
           aktualny->wyswietl();
           aktualny = aktualny->pNastepnyEmelemt;
       }
   }
}

void ListaZetonow::dodajZeton(Zeton* pZeton) {
    ElementListy* nowyElement = new ElementListy(pZeton);
    if (pierwszy == nullptr) {
        pierwszy = nowyElement;
    } else {
        ElementListy* aktualny = pierwszy;
        while (aktualny->pNastepnyEmelemt != nullptr) {
            aktualny = aktualny->pNastepnyEmelemt;
        }
        aktualny->pNastepnyEmelemt = nowyElement;
    }
}

void ListaZetonow::usunElement(Zeton* zeton) {
    if (pierwszy == nullptr) {
        std::cout << "Lista jest pusta." << std::endl;
        return;
    }

    ElementListy* aktualny = pierwszy;
    ElementListy* poprzedni = nullptr;

    while (aktualny != nullptr and aktualny->pEmelemt != zeton) {
        poprzedni = aktualny;
        aktualny = aktualny->pNastepnyEmelemt;
    }

    if (aktualny == nullptr) {
        std::cout << "Zeton nie istnieje w liscie." << std::endl;
        return;
    }

    if (poprzedni == nullptr) {
        pierwszy = aktualny->pNastepnyEmelemt;
    } else {
        poprzedni->pNastepnyEmelemt = aktualny->pNastepnyEmelemt;
    }

    delete aktualny;
}

void ListaZetonow::polonczListy(const ListaZetonow& lista) {
    if (pierwszy == nullptr) {
        pierwszy = lista.pierwszy;
    } else {
        ElementListy* aktualny = pierwszy;
        while (aktualny->pNastepnyEmelemt != nullptr) {
            aktualny = aktualny->pNastepnyEmelemt;
        }
        aktualny->pNastepnyEmelemt = lista.pierwszy;
    }
}

ListaZetonow ListaZetonow::podzielListy(int indeks) {
    ListaZetonow lista1;

    if (pierwszy == nullptr or indeks <= 0) {
        return lista1;
    }

    if (indeks == 1) {
        lista1.pierwszy = pierwszy;
        pierwszy = nullptr;
        return lista1;
    }

    ElementListy* aktualny = pierwszy;
    int licznik = 1;

    while (aktualny != nullptr and licznik < indeks) {
        aktualny = aktualny->pNastepnyEmelemt;
        licznik++;
    }

    if (aktualny == nullptr) {
        return lista1;
    }

    lista1.pierwszy = aktualny->pNastepnyEmelemt;
    aktualny->pNastepnyEmelemt = nullptr;

    return lista1;
}

ListaZetonow::Iterator::Iterator(ElementListy* elem) : aktualny(elem) {}

ListaZetonow::Iterator& ListaZetonow::Iterator::operator++() {
    if (aktualny != nullptr) {
        aktualny = aktualny->pNastepnyEmelemt;
    }
    return *this;
}

bool ListaZetonow::Iterator::operator!=(const Iterator& other) const {
    return aktualny != other.aktualny;
}

Zeton* ListaZetonow::Iterator::operator*() const {
    return aktualny->pEmelemt;
}

ListaZetonow::Iterator ListaZetonow::begin() const {
    return Iterator(pierwszy);
}

ListaZetonow::Iterator ListaZetonow::end() const {
    return Iterator(nullptr);
}


////////////////////////////////////


void ListaZetonow::testListy() {
    auto z1 = new ZetonCyfra{0,1, 'B'};
    auto z2 = new ZetonCyfra{0,2, 'B'};
    auto z3 = new ZetonCyfra{0,3, 'B'};
    auto z11 = new ZetonCyfra{0,1, 'G'};
    auto z22 = new ZetonCyfra{0,2, 'G'};
    auto z33 = new ZetonCyfra{0,3, 'Y'};
    ListaZetonow lista1;
    ListaZetonow lista2;
    lista2.dodajZeton(z11);
    lista2.dodajZeton(z22);
    lista2.dodajZeton(z33);
    lista1.dodajZeton(z1);
    lista1.dodajZeton(z2);
    lista1.dodajZeton(z3);



    std::cout << "\nlista1: ";
    lista1.wyswietlListe();
    std::cout << "\nlista2: ";
    lista2.wyswietlListe();

    lista1.polonczListy(lista2);
    std::cout << "\nlista1 po polonczniu z lista2: ";
    lista1.wyswietlListe();

    std::cout << "\nlista1 podzial po 4: ";
    ListaZetonow lista3 = lista1.podzielListy(4);
    lista1.wyswietlListe();

    ///iter
    std::cout << "\nlista1 for: ";
    for (auto zeton : lista1) {
        zeton->pokazZeton();
    }

    ListaZetonow::Iterator iter = lista1.begin();
    std::cout << "\nlista1 begin i iter++: ";
    iter.operator*()->pokazZeton();

    iter.operator++();
    iter.operator*()->pokazZeton();

    ///

    std::cout << "\nlista3 utworzona po podziale: ";
    lista3.wyswietlListe();

    std::cout << "\nlista1 usuwanie elemnetow: ";
    std::cout << std::endl;
    lista1.usunElement(z1);
    lista1.wyswietlListe();
    std::cout << std::endl;
    lista1.usunElement(z3);
    lista1.wyswietlListe();
    std::cout << std::endl;
    lista1.usunElement(z2);
    lista1.wyswietlListe();

}


