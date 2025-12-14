#ifndef DINAMICKI_NIZ_HPP
#define DINAMICKI_NIZ_HPP

#include <iostream>

using namespace std;

#define KAPACITET               (3)
#define UVECANJE_KAPACITETA     (2)

class DinamickiNiz {
private:
    double *_elementi;
    int _kapacitet;
    int _velicina;
public:
    DinamickiNiz(int kapacitet = KAPACITET);

    // moramo ih predefinisati jer podrazumevana implementacija brise/kopira vrednost pokazivaca
    // a ne ono na sta pokazuje 
    ~DinamickiNiz();
    DinamickiNiz(const DinamickiNiz &niz);
    DinamickiNiz& operator = (const DinamickiNiz &niz);

    double& operator[] (int indeks);
    const double& operator[] (int indeks) const;
    void dodajNaKraj(double element);
    void ispisi(ostream &izlaz) const;
};

ostream& operator << (ostream &izlaz, const DinamickiNiz &niz);

#endif