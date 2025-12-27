#include <iostream>
#include "Izrazi.hpp"

using namespace std;

int main() {
    TablicaSimbola t;
    t.dodajPromenljivu("x", 5);
    t.dodajPromenljivu("y", -1);

    // 1 * x + sin(0)
    Izraz *i = new Zbir(
        new Proizvod(new Konstanta(1), new Promenljiva("x")),
        new Sinus(new Konstanta(0))
    );
    Izraz *izvod_i = i->izvod("x");

    cout << *i << " = " << i->izracunaj(t) << endl;
    cout << *izvod_i << " = " << izvod_i->izracunaj(t) << endl;

    delete i;
    delete izvod_i;

    return 0;
}