#include "DinamickiNiz.hpp"

DinamickiNiz::DinamickiNiz(int kapacitet) 
    : _kapacitet(kapacitet), _velicina(0) {
    _elementi = new double[_kapacitet];
}

DinamickiNiz::DinamickiNiz(const DinamickiNiz &niz) {
    _kapacitet = niz._kapacitet;
    _velicina = niz._velicina;
    _elementi = new double[_kapacitet];

    for (int i = 0; i < _velicina; i++) {
        _elementi[i] = niz._elementi[i];
    }
}

DinamickiNiz& DinamickiNiz::operator = (const DinamickiNiz &niz) {
    if (this == &niz) {
        return *this;
    }

    _kapacitet = niz._kapacitet;
    _velicina = niz._velicina;
    if (_elementi != nullptr) {
        delete[] _elementi;
    }
    _elementi = new double[_kapacitet];

    for (int i = 0; i < _velicina; i++) {
        _elementi[i] = niz._elementi[i];
    }

    return *this;
}

DinamickiNiz::~DinamickiNiz() {
    // brisanje citavog niza
    delete[] _elementi;
}

void DinamickiNiz::dodajNaKraj(double element) {
    if (_velicina >= _kapacitet) {
        _kapacitet *= UVECANJE_KAPACITETA;
        double *noviNiz = new double[_kapacitet];
        for (int i = 0; i < _velicina; i++) {
            noviNiz[i] = _elementi[i];
        }
        delete[] _elementi;
        _elementi = noviNiz;
    }
    _elementi[_velicina++] = element;
}

void DinamickiNiz::ispisi(ostream &izlaz) const {
    izlaz << "[ ";
    for (int i = 0; i < _velicina; i++) {
        izlaz << _elementi[i] << " ";
    }
    izlaz << "]";
}

double& DinamickiNiz::operator[] (int indeks) {
    if (indeks >= _velicina || indeks < 0) {
        throw "Nevalidan indeks!";
    }
    return _elementi[indeks];
}

const double& DinamickiNiz::operator[] (int indeks) const {
    if (indeks >= _velicina || indeks < 0) {
        throw "Nevalidan indeks!";
    }
    return _elementi[indeks];
}

ostream& operator << (ostream &izlaz, const DinamickiNiz &niz) {
    niz.ispisi(izlaz);
    return izlaz;
}
