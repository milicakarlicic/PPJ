#ifndef DINAMICKI_NIZ_HPP
#define DINAMICKI_NIZ_HPP

#include <iostream>

#define INICIJALNI_KAPACITET       (3)

class DinamickiNiz {
public:
    DinamickiNiz();
    DinamickiNiz(const DinamickiNiz& niz);
    // DinamickiNiz(const DinamickiNiz& niz) = delete; ako hocemo da zabranimo koriscenje
    ~DinamickiNiz();

    void dodaj(double element);
    void ispisi(std::ostream& izlaz) const;

    DinamickiNiz& operator=(const DinamickiNiz& niz);
    // DinamickiNiz& operator=(const DinamickiNiz& niz) = delete; ako hocemo da zabranimo koriscenje
    double& operator[](int indeks);
private:
    // podrazumevani destruktor, konstruktor kopije i operator= nisu dovoljni zbog dinamicke alokacije 
    double* m_elementi; 
    int m_kapacitet;
    int m_brojElemenata;
};

std::ostream& operator<<(std::ostream& izlaz, const DinamickiNiz& niz);

#endif
