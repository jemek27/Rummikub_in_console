//
// Created by jemek on 21.04.2023.
//

#include "../headers/Joker.h"

void Joker::pokazZeton() {
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 1);

    std::cout << "[JK";
    if (tempCyfra !=27) std::cout  << tempCyfra << tempKolor;

    std::cout << "]";
    SetConsoleTextAttribute(hConsole, 7);
}

int Joker::dajWartosc() {
    return tempCyfra;
}

char Joker::dajKolor() {
    return tempKolor;
}

bool Joker::nadajWartosciZetonowe(int i, char c) {
    if (0 < i and i < 14) {
        tempCyfra = i;
    } else {
        std::cout << "Dozwolone wartosci <1, 13>\n";
        return false;
    }

    char upperC = toupper(c);
    switch (upperC) {
        case 'Y':
        case 'B':
        case 'R':
        case 'G':
            tempKolor = upperC;
            return true;
        default:
            std::cout << "Dozwolone kolory { R, G, B, Y }\n";
            return false;
    }
}


bool Joker::operator==(Zeton &inny) {
    bool wynik = false;
    if (tempCyfra == inny.cyfra and tempKolor == inny.kolor) wynik = true;
    return wynik;
}

bool Joker::operator<(Zeton &inny) {
    bool wynik = false;
    if (tempCyfra < inny.cyfra or (tempCyfra == inny.cyfra and tempKolor < inny.kolor)) wynik = true;
    return wynik;
}

Joker::operator int() {
    return tempCyfra;
}

void Joker::display(std::ostream &os) const {
    os << "Joker: ";
    Zeton::display(os);
    os << ", T:[" << tempCyfra <<  tempKolor << "]";
}

void Joker::read(std::istream &is) {
    Zeton::read(is);
    is >> tempCyfra >> tempKolor;
}

