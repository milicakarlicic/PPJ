#ifndef GRAF_HPP
#define GRAF_HPP

#include <iostream>
#include <map>
#include <set>

class Graf {
public:
    Graf();
    Graf(const std::map<int, std::set<int>>& graf);

    void ispisiUsmereno() const;
    void ispisiNeusmereno() const;
    void obrisiCvor(int cvor);
    void ispisiSusede(int cvor) const;
    Graf operator+(const Graf& g) const;
    Graf operator*(const Graf& g) const;
    Graf operator~() const;
private:
    int _maxCvor;
    std::map<int, std::set<int>> _graf;
};

int nadjiMaxCvor(const std::map<int, std::set<int>>& graf);

#endif