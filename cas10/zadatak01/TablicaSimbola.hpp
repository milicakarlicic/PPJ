#ifndef TABLICA_SIMBOLA_HPP
#define TABLICA_SIMBOLA_HPP

#include <map>
#include <stdexcept>

class TablicaSimbola {
public:
    void dodajPromenljivu(const std::string& id, int i);
    int vratiVrednost(const std::string& id) const;
private:
    std::map<std::string, int> _promenljive;
};

#endif