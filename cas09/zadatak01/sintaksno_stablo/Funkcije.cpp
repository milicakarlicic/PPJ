#include "Funkcije.hpp"
#include <cmath>

////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const Funkcija& f) {
    f.ispisi(izlaz);
    return izlaz;
}

//////////////////////////////////////////

KonstantaFunkcija::KonstantaFunkcija(double vrednost)
    : _vrednost(vrednost) {}

void KonstantaFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << _vrednost;
}

double KonstantaFunkcija::izracunaj(double vrednost) const {
    return _vrednost;
}

Funkcija* KonstantaFunkcija::kompozicija(Funkcija* f) const {
    return new KonstantaFunkcija(*this);
}

Funkcija* KonstantaFunkcija::izvod() const {
    return new KonstantaFunkcija(0);
}

Funkcija* KonstantaFunkcija::kopija() const {
    return new KonstantaFunkcija(*this);
}

////////////////////////////////////////

IdentitetFunkcija::IdentitetFunkcija() {}

void IdentitetFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "x";
}

double IdentitetFunkcija::izracunaj(double vrednost) const {
    return vrednost;
}

Funkcija* IdentitetFunkcija::kompozicija(Funkcija* f) const {
    // Pravimo kopiju da bismo bezbjedno obrisali kompoziciju u parseru - ostale klase prave nove funkcije
    return f->kopija();
}

Funkcija* IdentitetFunkcija::izvod() const {
    return new KonstantaFunkcija(1);
}

Funkcija* IdentitetFunkcija::kopija() const {
    return new IdentitetFunkcija(*this);
}

////////////////////////////////////////

UnarnaFunkcija::UnarnaFunkcija(Funkcija* operand)
    : _operand(operand) {}

UnarnaFunkcija::UnarnaFunkcija(const UnarnaFunkcija& f) {
    _operand = f._operand->kopija();
}

UnarnaFunkcija::~UnarnaFunkcija() {
    delete _operand;
}

SinFunkcija::SinFunkcija(Funkcija* operand)
    : UnarnaFunkcija(operand) {}

void SinFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "sin(" << *_operand << ")";
}

double SinFunkcija::izracunaj(double vrednost) const {
    return sin(_operand->izracunaj(vrednost));
}

Funkcija* SinFunkcija::kompozicija(Funkcija* f) const {
    return new SinFunkcija(_operand->kompozicija(f));
}

Funkcija* SinFunkcija::izvod() const {
    return new MnozenjeFunkcija(
        new CosFunkcija(_operand->kopija()),
        _operand->izvod()
    );
}

Funkcija* SinFunkcija::kopija() const {
    return new SinFunkcija(*this);
}

CosFunkcija::CosFunkcija(Funkcija* operand)
    : UnarnaFunkcija(operand) {}

void CosFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "cos(" << *_operand << ")";
}

double CosFunkcija::izracunaj(double vrednost) const {
    return cos(_operand->izracunaj(vrednost));
}

Funkcija* CosFunkcija::kompozicija(Funkcija* f) const {
    return new CosFunkcija(_operand->kompozicija(f));
}

Funkcija* CosFunkcija::izvod() const {
    return new MnozenjeFunkcija(
        new KonstantaFunkcija(-1),
        new MnozenjeFunkcija(
            new SinFunkcija(_operand->kopija()),
            _operand->izvod()
        )
    );
}

Funkcija* CosFunkcija::kopija() const {
    return new CosFunkcija(*this);
}

UnMinusFunkcija::UnMinusFunkcija(Funkcija* operand)
    : UnarnaFunkcija(operand) {}

void UnMinusFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "- (" << *_operand << ")";
}

double UnMinusFunkcija::izracunaj(double vrednost) const {
    return -_operand->izracunaj(vrednost);
}

Funkcija* UnMinusFunkcija::kompozicija(Funkcija* f) const {
    return new UnMinusFunkcija(_operand->kompozicija(f)); // f(x)=-x // f(x^2)
}

Funkcija* UnMinusFunkcija::izvod() const {
    return new UnMinusFunkcija(_operand->izvod());
}

Funkcija* UnMinusFunkcija::kopija() const {
    return new UnMinusFunkcija(*this);
}

////////////////////////////////////////

BinarnaFunkcija::BinarnaFunkcija(Funkcija* levi, Funkcija* desni)
    : _levi(levi), _desni(desni) {}

BinarnaFunkcija::BinarnaFunkcija(const BinarnaFunkcija& f) {
    _levi = f._levi->kopija();
    _desni = f._desni->kopija();
}

BinarnaFunkcija::~BinarnaFunkcija() {
    delete _levi;
    delete _desni;
}

SabiranjeFunkcija::SabiranjeFunkcija(Funkcija* levi, Funkcija* desni)
    : BinarnaFunkcija(levi, desni) {}

void SabiranjeFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "(" << *_levi << ") + (" << *_desni << ")";
}

double SabiranjeFunkcija::izracunaj(double vrednost) const {
    return _levi->izracunaj(vrednost) + _desni->izracunaj(vrednost);
}

Funkcija* SabiranjeFunkcija::kompozicija(Funkcija* f) const {
    return new SabiranjeFunkcija(_levi->kompozicija(f), _desni->kompozicija(f));
}

Funkcija* SabiranjeFunkcija::izvod() const {
    return new SabiranjeFunkcija(_levi->izvod(), _desni->izvod());
}

Funkcija* SabiranjeFunkcija::kopija() const {
    return new SabiranjeFunkcija(*this);
}

OduzimanjeFunkcija::OduzimanjeFunkcija(Funkcija* levi, Funkcija* desni)
    : BinarnaFunkcija(levi, desni) {}

void OduzimanjeFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "(" << *_levi << ") - (" << *_desni << ")";
}

double OduzimanjeFunkcija::izracunaj(double vrednost) const {
    return _levi->izracunaj(vrednost) - _desni->izracunaj(vrednost);
}

Funkcija* OduzimanjeFunkcija::kompozicija(Funkcija* f) const {
    return new OduzimanjeFunkcija(_levi->kompozicija(f), _desni->kompozicija(f));
}

Funkcija* OduzimanjeFunkcija::izvod() const {
    return new OduzimanjeFunkcija(_levi->izvod(), _desni->izvod());
}

Funkcija* OduzimanjeFunkcija::kopija() const {
    return new OduzimanjeFunkcija(*this);
}

MnozenjeFunkcija::MnozenjeFunkcija(Funkcija* levi, Funkcija* desni)
    : BinarnaFunkcija(levi, desni) {}

void MnozenjeFunkcija::ispisi(std::ostream& izlaz) const {
    izlaz << "(" << *_levi << ") * (" << *_desni << ")";
}

double MnozenjeFunkcija::izracunaj(double vrednost) const {
    return _levi->izracunaj(vrednost) * _desni->izracunaj(vrednost);
}

Funkcija* MnozenjeFunkcija::kompozicija(Funkcija* f) const {
    return new MnozenjeFunkcija(_levi->kompozicija(f), _desni->kompozicija(f));
}

Funkcija* MnozenjeFunkcija::izvod() const {
    return new SabiranjeFunkcija(
        new MnozenjeFunkcija(_levi->izvod(), _desni->kopija()),
        new MnozenjeFunkcija(_levi->kopija(), _desni->izvod())
    );
}

Funkcija* MnozenjeFunkcija::kopija() const {
    return new MnozenjeFunkcija(*this);
}
