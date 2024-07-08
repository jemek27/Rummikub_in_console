//
// Created by jemek on 21.04.2023.
//

#include "../headers/Zeton.h"


void Zeton::display(std::ostream &os) const {
    os << "[" << cyfra << kolor << "], ID: " << idZetonu;
}

void Zeton::read(std::istream &is) {
    is >> cyfra >> kolor;
}

std::ostream &operator<<(std::ostream &os, const Zeton &zeton) {
    zeton.display(os);
    return os;
}

std::istream &operator>>(std::istream &is, Zeton &zeton) {
    zeton.read(is);
    return is;
}
