cmake_minimum_required(VERSION 3.23)
project(Rummikub)

set(CMAKE_CXX_STANDARD 20)

add_executable(Rummikub main.cpp src/WorekNaZetony.cpp headers/WorekNaZetony.h src/TabliczkaGracza.cpp headers/TabliczkaGracza.h src/Zeton.cpp headers/Zeton.h src/Joker.cpp headers/Joker.h src/CiagZetonow.cpp headers/CiagZetonow.h src/ZetonCyfra.cpp headers/ZetonCyfra.h src/Plansza.cpp headers/Plansza.h src/Menu.cpp headers/Menu.h src/ElementListy.cpp headers/ElementListy.h src/ListaZetonow.cpp headers/ListaZetonow.h src/testowanie.cpp headers/testowanie.h src/OdczytZapisyDoPliku.cpp headers/OdczytZapisyDoPliku.h)

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()