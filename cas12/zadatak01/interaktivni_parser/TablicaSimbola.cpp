#include "TablicaSimbola.hpp"

TablicaSimbola::~TablicaSimbola() {
    for (auto& par : _promenljive) {
        delete par.second;
    }
}

bool TablicaSimbola::postojiPromenljiva(const std::string& id) const {
    return _promenljive.find(id) != _promenljive.end();
}


void TablicaSimbola::dodajPromenljivu(const std::string& id, Graf* g) {
    if (postojiPromenljiva(id)) {
        delete _promenljive[id];
    }
    _promenljive[id] = g;
}

Graf* TablicaSimbola::vratiPromenljivu(const std::string& id) const {
    if (!postojiPromenljiva(id)) {
        throw "Ne postoji promenljiva";
    }
    return _promenljive.at(id);
}