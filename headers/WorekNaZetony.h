//
// Created by jemek on 21.04.2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Zeton.h"
#include "Joker.h"
#include "ZetonCyfra.h"

#ifndef RUMMIKUB_WOREKNAZETONY_H
#define RUMMIKUB_WOREKNAZETONY_H


class WorekNaZetony {
public:
    std::vector<Zeton*> vectorZetonow;
    explicit WorekNaZetony (int iloscGraczy);
    ~WorekNaZetony();
    void test ();
};


#endif //RUMMIKUB_WOREKNAZETONY_H
