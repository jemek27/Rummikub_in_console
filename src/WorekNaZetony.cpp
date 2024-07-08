//
// Created by jemek on 21.04.2023.
//

#include "../headers/WorekNaZetony.h"

WorekNaZetony::WorekNaZetony(int iloscGraczy) {
    int idZetonow = 0;
    if (iloscGraczy <= 4) {
        for (int i = 0; i < 2; i++) {
            for (int cyfraZetonu = 1; cyfraZetonu <= 13; cyfraZetonu++) {
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'R'});
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'G'});
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'B'});
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'Y'});
            }
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            for (int cyfraZetonu = 1; cyfraZetonu <= 13; cyfraZetonu++) {
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'R'});
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'G'});
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'B'});
                vectorZetonow.push_back(new ZetonCyfra{idZetonow++, cyfraZetonu, 'Y'});
            }
        }
        vectorZetonow.push_back(new Joker{idZetonow++});
        vectorZetonow.push_back(new Joker{idZetonow++});
    }
    vectorZetonow.push_back(new Joker{idZetonow++});
    vectorZetonow.push_back(new Joker{idZetonow++});

    auto rd = std::random_device {};
    auto rng = std::default_random_engine {rd()};
    std::shuffle(std::begin(vectorZetonow), std::end(vectorZetonow), rng);

}

void WorekNaZetony::test() {
    for (auto z : vectorZetonow)
    z->pokazZeton();
}

WorekNaZetony::~WorekNaZetony() {
    for(auto z : vectorZetonow)
        delete z;
}
