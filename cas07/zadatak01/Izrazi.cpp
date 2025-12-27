#include "Izrazi.hpp"

using namespace std;

////////////////////////////////////////////////

bool TablicaSimbola::dodajPromenljivu(const string &naziv, double vrednost) {
    auto it = promenljive.find(naziv);
    if (it != promenljive.end()) {
        return false;
    }
    promenljive[naziv] = vrednost;
    return true;
}

bool TablicaSimbola::definisanaPromenljiva(const string &naziv) const {
    auto it = promenljive.find(naziv);
    return it != promenljive.end();
}

double TablicaSimbola::vrednostPromenljive(const string &naziv) const {
    auto it = promenljive.find(naziv);
    if (it == promenljive.end()) {
        throw "Promenljiva nije definisana!";
    }

    return it->second; 
}

////////////////////////////////////////////////

ostream& operator << (ostream &izlaz, const Izraz &i) {
    i.ispis(izlaz);
    return izlaz;
}

////////////////////////////////////////////////

void Konstanta::ispis(ostream &izlaz) const {
    izlaz << _vrednost;
}

double Konstanta::izracunaj(const TablicaSimbola &t) const {
    return _vrednost;
}

Izraz* Konstanta::izvod(const string &prom) const {
    return new Konstanta(0);
}

Izraz* Konstanta::kopija() const {
    return new Konstanta(*this);
}

////////////////////////////////////////////////

void Promenljiva::ispis(std::ostream &izlaz) const {
    izlaz << _naziv;
}

double Promenljiva::izracunaj(const TablicaSimbola &t) const {
    if (!t.definisanaPromenljiva(_naziv)) {
        throw "Promenljiva nije definisana!";
    }
    return t.vrednostPromenljive(_naziv);
}

Izraz* Promenljiva::izvod(const string &prom) const {
    return _naziv == prom ? new Konstanta(1) : new Konstanta(0);
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

Izraz* Sinus::izvod(const string &naziv) const {
    // sin(i)' = cos(i)*i'
    return new Proizvod(new Kosinus(_operand->kopija()), _operand->izvod(naziv));
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

Izraz* Kosinus::izvod(const string &prom) const {
    // cos(i) = -1*sin(i)*i'
    return new Proizvod(
        new Proizvod(new Konstanta(-1), new Sinus(_operand->kopija()))
        , _operand->izvod(prom));
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

Izraz* Zbir::izvod(const string &prom) const {
    return new Zbir(_levi->izvod(prom), _desni->izvod(prom));
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

Izraz* Proizvod::izvod(const string &prom) const {
    // xy = x'y + xy'
    return new Zbir(
        new Proizvod(_levi->izvod(prom), _desni->kopija()),
        new Proizvod(_levi->kopija(), _desni->izvod(prom))
    );
}

Izraz* Proizvod::kopija() const {
    return new Proizvod(*this);
}