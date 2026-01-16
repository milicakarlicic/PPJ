#include "Izrazi.hpp"

////////////////////////////////////////////////

bool TablicaSimbola::dodajPromenljivu(const std::string &id, double vrednost) {
    auto it = _promenljive.find(id);
    if (it != _promenljive.end()) {
        return false;
    }
    _promenljive[id] = vrednost;
    return true;
}

bool TablicaSimbola::definisanaPromenljiva(const std::string &id) const {
    auto it = _promenljive.find(id);
    return it != _promenljive.end();
}

double TablicaSimbola::vrednostPromenljive(const std::string &id) const {
    auto it = _promenljive.find(id);
    if (it == _promenljive.end()) {
        throw "Promenljiva nije definisana!";
    }

    return it->second; 
}

////////////////////////////////////////////////

std::ostream& operator << (std::ostream &izlaz, const Izraz &i) {
    i.ispis(izlaz);
    return izlaz;
}

////////////////////////////////////////////////

void Konstanta::ispis(std::ostream &izlaz) const {
    izlaz << _vrednost;
}

double Konstanta::izracunaj(const TablicaSimbola &t) const {
    return _vrednost;
}

Izraz* Konstanta::izvod(const std::string &id) const {
    return new Konstanta(0);
}

Izraz* Konstanta::kopija() const {
    return new Konstanta(*this);
}

////////////////////////////////////////////////

void Promenljiva::ispis(std::ostream &izlaz) const {
    izlaz << _id;
}

double Promenljiva::izracunaj(const TablicaSimbola &t) const {
    if (!t.definisanaPromenljiva(_id)) {
        throw "Promenljiva nije definisana!";
    }
    return t.vrednostPromenljive(_id);
}

Izraz* Promenljiva::izvod(const std::string &id) const {
    return _id == id ? new Konstanta(1) : new Konstanta(0);
}

Izraz* Promenljiva::kopija() const {
    return new Promenljiva(*this);
}

////////////////////////////////////////////////

void Sinus::ispis(std::ostream &izlaz) const {
    izlaz << "sin(" << *_operand << ")";
}

double Sinus::izracunaj(const TablicaSimbola &t) const {
    return sin(_operand->izracunaj(t));
}

Izraz* Sinus::izvod(const std::string &id) const {
    // sin(i)' = cos(i)*i'
    return new Proizvod(new Kosinus(_operand->kopija()), _operand->izvod(id));
}

Izraz* Sinus::kopija() const {
    return new Sinus(*this);
}

void Kosinus::ispis(std::ostream &izlaz) const {
    izlaz << "cos(" << *_operand << ")";
}

double Kosinus::izracunaj(const TablicaSimbola &t) const {
    return cos(_operand->izracunaj(t));
}

Izraz* Kosinus::izvod(const std::string &id) const {
    // cos(i) = -1*sin(i)*i'
    return new Proizvod(
        new Proizvod(new Konstanta(-1), new Sinus(_operand->kopija()))
        , _operand->izvod(id));
}

Izraz* Kosinus::kopija() const {
    return new Kosinus(*this);
}

////////////////////////////////////////////////

void Zbir::ispis(std::ostream &izlaz) const {
    // () + ()
    izlaz << "(" << *_levi << ") + (" << *_desni << ")";
}  

double Zbir::izracunaj(const TablicaSimbola &t) const {
    return _levi->izracunaj(t) + _desni->izracunaj(t);
}

Izraz* Zbir::izvod(const std::string &id) const {
    return new Zbir(_levi->izvod(id), _desni->izvod(id));
}

Izraz* Zbir::kopija() const {
    return new Zbir(*this);
}

void Proizvod::ispis(std::ostream &izlaz) const {
    izlaz << "(" << *_levi << ") * (" << *_desni << ")";
}  

double Proizvod::izracunaj(const TablicaSimbola &t) const {
    return _levi->izracunaj(t) * _desni->izracunaj(t);
}

Izraz* Proizvod::izvod(const std::string &id) const {
    // xy = x'y + xy'
    return new Zbir(
        new Proizvod(_levi->izvod(id), _desni->kopija()),
        new Proizvod(_levi->kopija(), _desni->izvod(id))
    );
}

Izraz* Proizvod::kopija() const {
    return new Proizvod(*this);
}