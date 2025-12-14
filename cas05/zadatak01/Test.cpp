#include <iostream>

#include "DinamickiNiz.hpp"

using namespace std;

int main() {
    // konstruktor bez argumenata
    DinamickiNiz niz;

    niz.dodajNaKraj(1);
    niz.dodajNaKraj(3);
    niz.dodajNaKraj(-5);
    niz.dodajNaKraj(4.5);
    cout << niz << endl;

    // konstruktor kopije
    DinamickiNiz niz2(niz);
    cout << niz2 << endl;

    DinamickiNiz niz3;
    // operator dodele
    niz3 = niz; 
    cout << niz3 << endl;

    try {
        niz3[3] = 101;
        cout << niz3 << endl;

        cout << niz3[-1] << endl;
    } catch (const char *poruka) {
        cerr << poruka << endl;
    }

    return 0;
}