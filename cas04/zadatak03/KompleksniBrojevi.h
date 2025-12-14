#ifndef KOMPLEKSNI_H
#define KOMPLEKSNI_H

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class KompleksanBroj {
private:
    double _realni;
    double _imaginarni;
public:
    // klasa nema pokazivacko polje pa su dovoljni podrazumevani destruktor, konstruktor kopije i operator =
    KompleksanBroj(double realni = 0, double imaginarni = 0);

    void ispisi(ostream &izlaz) const;
    void ucitaj(istream &ulaz);

    KompleksanBroj operator + (const KompleksanBroj &z) const;
    KompleksanBroj operator / (const KompleksanBroj &z) const;
    // postfiksni i prefiksni operator inkrementiranja (dekrementiranja) se 
    // razlikuju po tome sto postfiksni ima fiktivni argument int: operator++ (int)

    bool operator == (const KompleksanBroj &z) const;
};

ostream& operator << (ostream &izlaz, const KompleksanBroj &z);
istream& operator >> (istream &ulaz, KompleksanBroj &z);

#endif

