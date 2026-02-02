#include "TablicaSimbola.hpp"

TablicaSimbola::~TablicaSimbola() {
    for (auto par : _funkcije) {
        delete par.second;
    }
}

bool TablicaSimbola::postojiFunkcija(const std::string& id) const {
    return _funkcije.find(id) != _funkcije.end();
}

void TablicaSimbola::dodajFunkciju(const std::string& id, Funkcija* f) {
    if (postojiFunkcija(id)) {
        auto it = _funkcije.find(id);
        delete it->second;
    }
    _funkcije[id] = f;
}

Funkcija* TablicaSimbola::vratiFunkciju(const std::string& id) const {
    if (!postojiFunkcija(id)) {
        throw "Ne postoji funkcija!";
    }
    auto it = _funkcije.find(id);
    return it->second; 
}