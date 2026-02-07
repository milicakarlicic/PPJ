#ifndef TABLICA_SIMBOLA_HPP
#define TABLICA_SIMBOLA_HPP

#include "Graf.hpp"

class TablicaSimbola {
public:
    ~TablicaSimbola();

    void dodajPromenljivu(const std::string& id, Graf* g);
    Graf* vratiPromenljivu(const std::string& id) const;
    bool postojiPromenljiva(const std::string& id) const;
private:
    std::map<std::string, Graf*> _promenljive;
};

#endif