#include <iostream>
#include "KompleksniBrojevi.h"

using namespace std;

int main() {
    KompleksanBroj z1(1, 1); 
    KompleksanBroj z2 = KompleksanBroj(1, -2);
    cout << z1 << endl;
    cout << z2 << endl;

    // pokazivac
    KompleksanBroj *z3 = &z1;
    cout << *z3 << endl;

    // referenca - semantika pokazivaca, sintaksa obicne promenljive
    KompleksanBroj &z4 = z1;
    cout << z4 << endl;

    // konstruktor kopije - nismo definisali nas jer postoji podrazumevani i dovoljan nam je
    KompleksanBroj z5(z2);

    // operator dodele - nismo definisali nas jer postoji podrazumevani i dovoljan nam je
    z1 = KompleksanBroj(0, 0);
    try {
        cout << z1 / z1 << endl;
    } catch(const char *poruka) {
        cout << poruka << endl;
    }

    cin >> z1;
    cout << z1 << endl;

    return 0;

    // na kraju se poziva destruktor za sve objekte u stek okviru - podrazumevani dovoljan
}

