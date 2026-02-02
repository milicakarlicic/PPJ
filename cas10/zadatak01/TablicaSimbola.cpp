#include "TablicaSimbola.hpp"

void TablicaSimbola::dodajPromenljivu(const std::string& id, int i) {
    _promenljive[id] = i;
}

int TablicaSimbola::vratiVrednost(const std::string& id) const {
    auto it = _promenljive.find(id);
    if (it == _promenljive.end()) {
        throw std::invalid_argument("Promenljiva nije definisana");
    }
    return it->second;
}