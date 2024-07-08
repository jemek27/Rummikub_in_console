//
// Created by jemek on 15.06.2023.
//

#include "Zeton.h"

#ifndef RUMMIKUB_ELEMENTLISTY_H
#define RUMMIKUB_ELEMENTLISTY_H


class ElementListy {
public:
   Zeton* pEmelemt;
   ElementListy* pNastepnyEmelemt;
   ElementListy() : pEmelemt(nullptr), pNastepnyEmelemt(nullptr) {};
   ElementListy(Zeton* pZ) : pEmelemt(pZ), pNastepnyEmelemt(nullptr) {};
   void wyswietl();
};


#endif //RUMMIKUB_ELEMENTLISTY_H
