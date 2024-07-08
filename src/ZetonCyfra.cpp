//
// Created by jemek on 21.04.2023.
//

#include "../headers/ZetonCyfra.h"

void ZetonCyfra::pokazZeton() {
    HANDLE  hConsole;
    int k = 0;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (kolor) {
        case 'Y':
            k = 6;
            break;
        case 'B':
            k = 3;
            break;
        case 'G':
            k = 2;
            break;
        case 'R':
            k = 4;
            break;
    }

    SetConsoleTextAttribute(hConsole, k);
    std::cout << "[" << cyfra << kolor << "]";
    SetConsoleTextAttribute(hConsole, 7);
}

int ZetonCyfra::dajWartosc() {
    return cyfra;
}

char ZetonCyfra::dajKolor() {
    return kolor;
}


ZetonCyfra &ZetonCyfra::operator+(int n) {
    cyfra += n;
    return *this;
}

bool ZetonCyfra::nadajWartosciZetonowe(int i, char c) {return false;}

bool ZetonCyfra::operator==(ZetonCyfra &inny) {
    bool wynik = false;
    if (cyfra == inny.cyfra and kolor == inny.kolor) wynik = true;
    return wynik;
}

bool ZetonCyfra::operator<(ZetonCyfra &inny) {
    bool wynik = false;
    if (cyfra < inny.cyfra or (cyfra == inny.cyfra and kolor < inny.kolor)) wynik = true;
    return wynik;
}

ZetonCyfra::operator int() {
    return cyfra;
}

bool ZetonCyfra::operator==(Joker &joker) {
    if (cyfra == joker.dajWartosc() and kolor == joker.dajKolor()) return true;
    return false;
}

bool ZetonCyfra::operator<(Joker &joker) {
    if (cyfra < joker.dajWartosc() or (cyfra == joker.dajWartosc() and kolor < joker.dajKolor())) return true;
    return false;
}

void ZetonCyfra::display(std::ostream &os) const  {
    os << "ZetonCyfra: ";
    Zeton::display(os);
}

void ZetonCyfra::read(std::istream &is) {
    Zeton::read(is);
}

/*
std::ostream &operator<<(std::ostream &os, const Zeton &zeton) {
    os << "Cyfra: " << zeton.cyfra << ", Kolor: " << zeton.kolor << ", ID: " << zeton.idZetonu;
    return os;
}

std::istream &operator>>(std::istream &is, Zeton &zeton) {
    is >> zeton.cyfra >> zeton.kolor;
    return is;
}
*/



