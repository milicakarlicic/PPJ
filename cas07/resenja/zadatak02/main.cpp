#include <iostream>
#include "dinamicki_niz.hpp"

int main() {
    DinamickiNiz niz;

    niz.dodaj(4);
    niz.dodaj(-2);
    niz.dodaj(1);
    niz.dodaj(0);

    std::cout << niz << std::endl;

    DinamickiNiz niz2;
    niz2 = niz;

    try {
        niz[0] = 100;
        std::cout << niz << std::endl;
        std::cout << niz[-1] << std::endl;
    } catch (const char* poruka) {
        std::cerr << poruka << std::endl;
    }

    return 0;
}