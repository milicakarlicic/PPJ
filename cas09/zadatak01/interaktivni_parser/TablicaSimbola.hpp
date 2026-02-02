#ifndef TABLICA_SIMBOLA_HPP
#define TABLICA_SIMBOLA_HPP

#include <map>
#include <string>
#include "Funkcije.hpp"

class TablicaSimbola {
public:
    ~TablicaSimbola();

    void dodajFunkciju(const std::string& id, Funkcija* f);
    bool postojiFunkcija(const std::string& id) const;
    Funkcija* vratiFunkciju(const std::string& id) const;
private:
    std::map<std::string, Funkcija*> _funkcije;
};

#endif