#include "Polinom.hpp"

using namespace std;

Polinom::Polinom()
    : _koef() {}  

Polinom::Polinom(int stepen) 
    : _koef(stepen + 1, 0) {
    _koef[stepen] = 1;
}

Polinom::Polinom(const vector<double> &koef) 
    : _koef(koef) {}


void Polinom::ispisi(std::ostream &izlaz) const {
    if (_koef.size() == 0) {
        izlaz << "0";
        return;
    }

    for (int i = 0; i <= getStepen(); i++) {
        if (_koef[i] == 0) {
            continue;
        }
        
        if (_koef[i] < 0) {
            izlaz << " - ";
        } else if (i > 0) {
            izlaz << " + ";
        }

        izlaz << fabs(_koef[i]);

        if (i > 0) {
            izlaz << "x^" << i;
        }
    }
}

void Polinom::dodajKoef(double koef) {
    _koef.push_back(koef);
}

std::ostream& operator << (std::ostream &izlaz, const Polinom &p) {
    p.ispisi(izlaz);
    return izlaz;
}

Polinom Polinom::operator + (const Polinom& p) const {
    unsigned stepen = max(getStepen(), p.getStepen());
    vector<double> rezultat(stepen + 1);
    
    int i = 0;
    for(i = 0; i <= getStepen() && i <= p.getStepen(); i++)  {
        rezultat[i] = _koef[i] + p._koef[i];
    }

    for(; i <= getStepen(); i++) {
        rezultat[i] = _koef[i];
    }

    for(; i <= p.getStepen(); i++) {
        rezultat[i] = p._koef[i];
    }

    return Polinom(rezultat);
}

Polinom Polinom::operator - (const Polinom& p) const {
    unsigned stepen = max(getStepen(), p.getStepen());
    vector<double> rezultat(stepen + 1);

    int i;
    for(i = 0; i <= getStepen() && i <= p.getStepen(); i++) {
        rezultat[i] = _koef[i] - p._koef[i];
    }

    for(; i <= getStepen(); i++) {
        rezultat[i] = _koef[i];
    }

    for(; i <= p.getStepen(); i++) {
        rezultat[i] = - p._koef[i];
    }

    return Polinom(rezultat);
}

Polinom Polinom::operator * (const Polinom &p) const {
    vector<double> rezultat(getStepen() + p.getStepen() + 1);

    for (int i = 0; i <= getStepen(); i++) {
        for (int j = 0; j <= p.getStepen(); j++) {
            rezultat[i + j] += _koef[i] * p._koef[j];
        }
    }

    return Polinom(rezultat);
}

Polinom Polinom::operator - () const {
    vector<double> rezultat(getStepen() + 1);

    for(unsigned i = 0; i <= getStepen(); i++) {
        rezultat[i] = - _koef[i];
    }

    return Polinom(rezultat);
}

double Polinom::operator [] (double x) const {
    double vrednost = 0;
    double x_i = 1;

    for (int i = 0; i <= getStepen(); i++) {
        vrednost += _koef[i] * x_i;
        x_i *= x;
    }

    return vrednost;
}

int Polinom::getStepen() const {
    return _koef.size() - 1;
}

Polinom Polinom::izvod() const {
    vector<double> rezultat(_koef.size() - 1);

    for (int i = 1; i <= getStepen(); i++) {
        rezultat[i - 1] = _koef[i] * i;
    }

    return Polinom(rezultat);
}

Polinom Polinom::integral(double c) const {
    vector<double> rezultat(_koef.size() + 1);

    rezultat[0] = c;
    for (int i = 0; i <= getStepen(); i++) {
        rezultat[i + 1] = _koef[i] / (i + 1);
    }

    return Polinom(rezultat);
}

bool Polinom::operator == (const Polinom &p) const {
    if (getStepen() != p.getStepen()) {
        return false;
    }

    for (int i = 0; i <= getStepen(); i++) {
        if (_koef[i] != p._koef[i]) {
            return false;
        }
    }

    return true;
}

bool Polinom::operator != (const Polinom &p) const {
    return !(*this == p);
}