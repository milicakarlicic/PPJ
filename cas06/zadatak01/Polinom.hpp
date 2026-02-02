#ifndef POLINOMI_HPP
#define POLINOMI_HPP

#include <iostream>
#include <vector>
#include <cmath>

class Polinom {
public:
    Polinom();
    Polinom(int stepen);
    Polinom(const std::vector<double>& koef);

    void ispisi(std::ostream& izlaz) const;
    void dodajKoef(double koef);
    Polinom operator+(const Polinom& p) const;
    Polinom operator-(const Polinom& p) const;
    Polinom operator*(const Polinom& p) const;
    Polinom operator-() const;
    double operator[](double x) const;
    bool operator==(const Polinom& p) const;
    bool operator!=(const Polinom& p) const;
    int getStepen() const;
    Polinom izvod() const;
    Polinom integral(double c) const;
private: 
    std::vector<double> _koef;
};

std::ostream& operator<<(std::ostream& izlaz, const Polinom& p);

#endif