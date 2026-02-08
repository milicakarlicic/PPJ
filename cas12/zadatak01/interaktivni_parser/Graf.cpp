#include "Graf.hpp"

//////////////////////////////////////////////////////////

int nadjiMaxCvor(const std::map<int, std::set<int>>& graf) {
    // Ne moramo prolaziti kroz sve cvorove i njihove susede.
    // Svi cvorovi su kljucevi u mapi pa je dovoljno pronaci najveci kljuc.
    // Kako su kljucevi sortirani - uzmemo poslednji
    return graf.empty() ? 0 : graf.rbegin()->first;
}

//////////////////////////////////////////////////////////

Graf::Graf() 
    : _maxCvor(0) {}

Graf::Graf(const std::map<int, std::set<int>>& graf)
    : _maxCvor(nadjiMaxCvor(graf)), _graf(graf) {}

void Graf::ispisiUsmereno() const {
    for (int i = 1; i <= _maxCvor; i++) {
        for (int j = 1; j <= _maxCvor; j++) {
            if (_graf.find(i) != _graf.end() && 
            (_graf.at(i).find(j) != _graf.at(i).end())) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graf::ispisiNeusmereno() const {
    for (int i = 1; i <= _maxCvor; i++) {
        for (int j = 1; j <= _maxCvor; j++) {
            if (_graf.find(i) != _graf.end() && _graf.find(j) != _graf.end() && 
            (_graf.at(i).find(j) != _graf.at(i).end() ||
        _graf.at(j).find(i) != _graf.at(j).end())) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Graf Graf::operator+(const Graf& g) const {
    Graf rezultat(*this);

    for (auto& par : g._graf) {
        int cvor = par.first;
        auto& susedi = par.second;
        for (int sused : susedi) {
            rezultat._graf[cvor].insert(sused);
        }
    }

    rezultat._maxCvor = nadjiMaxCvor(rezultat._graf);

    return rezultat;
}

Graf Graf::operator*(const Graf& g) const {
    // Presek 2 grafa: presek cvorova i presek suseda za zajednicke cvorove
    Graf rezultat; 

    for (auto& par : _graf) {
        int cvor = par.first;
        if (g._graf.find(cvor) != g._graf.end()) {
            rezultat._graf[cvor];
            for (int sused : par.second) {
                if (g._graf.at(cvor).find(sused) != g._graf.at(cvor).end()) {
                    rezultat._graf[cvor].insert(sused);
                }
            }
        }
    }

    rezultat._maxCvor = nadjiMaxCvor(rezultat._graf);

    return rezultat;
}

Graf Graf::operator~() const {
    // Komplement grafa: isti cvorovi ali susedi su oni koji nisu susedi u originalnom grafu
    Graf rezultat;

    for (auto& par : _graf) {
        int cvor = par.first;
        rezultat._graf[cvor];
        auto& susedi = par.second;
        for (auto& par2 : _graf) {
            int i = par2.first;
            if (susedi.find(i) == susedi.end()) {
                rezultat._graf[cvor].insert(i);
            }
        }
    }

    rezultat._maxCvor = _maxCvor;

    return rezultat;
}

void Graf::obrisiCvor(int cvor) {
    _graf.erase(cvor);
    for (auto& par : _graf) {
        par.second.erase(cvor);
    }
    _maxCvor = nadjiMaxCvor(_graf);
}

void Graf::ispisiSusede(int cvor) const {
    if (_graf.find(cvor) != _graf.end()) {
        std::cout << "[";
        int i = 0;
        for (int sused : _graf.at(cvor)) {
            if (i == _graf.at(cvor).size() - 1) {
                std::cout << sused;
            } else {
                std::cout << sused << ", ";
            }
            i++;
        }
        std::cout << "]" << std::endl;
    } else {
        std::cout << "Cvor " << cvor << " ne postoji u grafu." << std::endl;
    }
}