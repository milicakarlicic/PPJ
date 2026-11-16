#include <iostream>
#include "kompleksni.hpp"

void f(KompleksanBroj& z) {
    // prenos argumenata po referenci
    z.setImaginarni(0);
}

int main() {
    KompleksanBroj z1(1, -3);
    KompleksanBroj z2(-5);
    KompleksanBroj z3;
    KompleksanBroj z4(z1); // podrazumevani konstruktor kopije

    std::cout << "--------------------\n";
    std::cout << z1 << " + " << z2 << std::endl;

    std::cout << "--------------------\n";
    try {
        std::cout << z1 << " / " << z1 << std::endl;
    } catch (const char* poruka) {
        std::cout << poruka << std::endl;
    }

    std::cout << "--------------------\n";
    if (z1 == z1) {
        std::cout << z1 << " == " << z1 << std::endl;
    } else {
        std::cout << z1 << " != " << z1 << std::endl;
    }

    std::cout << "--------------------\n";
    KompleksanBroj z5;
    std::cout << "Unesite kompleksan broj (realni i imaginarni deo): ";
    std::cin >> z5;
    std::cout << z5 << std::endl;

    return 0;
}