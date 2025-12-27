#ifndef KOMPLEKSNI_H
#define KOMPLEKSNI_H

#include <string>
#include <iostream>
#include <cmath>

class KompleksanBroj {
private:
    double _realni;
    double _imaginarni;
public:
    // klasa nema pokazivacko polje pa su dovoljni podrazumevani destruktor, konstruktor kopije i operator =
    KompleksanBroj(double realni = 0, double imaginarni = 0);

    void ispisi(std::ostream &izlaz) const;
    void ucitaj(std::istream &ulaz);

    KompleksanBroj operator + (const KompleksanBroj &z) const;
    KompleksanBroj operator / (const KompleksanBroj &z) const;
    
    // postfiksni i prefiksni operator inkrementiranja (dekrementiranja) se 
    // razlikuju po tome sto postfiksni ima fiktivni argument int: operator++ (int)

    bool operator == (const KompleksanBroj &z) const;
};

std::ostream& operator << (std::ostream &izlaz, const KompleksanBroj &z);
std::istream& operator >> (std::istream &ulaz, KompleksanBroj &z);

#endif

