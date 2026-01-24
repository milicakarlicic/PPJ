#include "SintaksnoStablo.hpp"
#include "Funkcije.hpp"

//////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const ASTCvor& f) {
    f.ispisi(izlaz);
    return izlaz;
}

//////////////////////////////////////////////////////////////

NizNaredbiCvor::~NizNaredbiCvor() {
    for (ASTCvor* naredba : _naredbe) {
        delete naredba;
    }
}

void NizNaredbiCvor::ispisi(std::ostream& izlaz) const {
    for (ASTCvor* naredba : _naredbe) {
        izlaz << *naredba << std::endl;
    }
}

Funkcija* NizNaredbiCvor::interpretiraj(TablicaSimbola& tablica) const {
    for (ASTCvor* naredba : _naredbe) {
        naredba->interpretiraj(tablica);
    }
    return nullptr;
}

void NizNaredbiCvor::dodajNaredbu(ASTCvor* naredba) {
    _naredbe.push_back(naredba);
}

//////////////////////////////////////////////////////////////
    
KonstantaCvor::KonstantaCvor(double vrednost)
    : _vrednost(vrednost) {}

void KonstantaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _vrednost;
}

Funkcija* KonstantaCvor::interpretiraj(TablicaSimbola& tablica) const {
    return new KonstantaFunkcija(_vrednost);
}

//////////////////////////////////////////////////////////////

PrazanCvor::PrazanCvor() {}

void PrazanCvor::ispisi(std::ostream& izlaz) const {}

Funkcija* PrazanCvor::interpretiraj(TablicaSimbola& tablica) const {
    return nullptr;
}

//////////////////////////////////////////////////////////////

IdentitetCvor::IdentitetCvor() {}

void IdentitetCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "x";
}

Funkcija* IdentitetCvor::interpretiraj(TablicaSimbola& tablica) const {
    return new IdentitetFunkcija();
}

//////////////////////////////////////////////////////////////

PromenljivaCvor::PromenljivaCvor(const std::string& id)
    : _id(id) {}

void PromenljivaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _id;
}

Funkcija* PromenljivaCvor::interpretiraj(TablicaSimbola& tablica) const {
    // Isto kao sto smo u interaktivnom parseru pravili kopiju u akciji za dohvatanje funkcije iz mape
    return tablica.vratiFunkciju(_id)->kopija();
}

//////////////////////////////////////////////////////////////

UnarniCvor::UnarniCvor(ASTCvor *operand)
    : _operand(operand) {}

UnarniCvor::~UnarniCvor() {
    delete _operand;
}

KompozicijaCvor::KompozicijaCvor(const std::string& id, ASTCvor *operand) 
    : UnarniCvor(operand), _id(id) {}

void KompozicijaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _id << "(" << *_operand << ")";
}

Funkcija* KompozicijaCvor::interpretiraj(TablicaSimbola& tablica) const {
    Funkcija* f = _operand->interpretiraj(tablica);
    Funkcija* rez = tablica.vratiFunkciju(_id)->kompozicija(f);
    // Brisanje isto kao u interaktivnom parseru
    delete f;

    return rez;
}

VrednostCvor::VrednostCvor(ASTCvor *operand, double vrednost)
    : UnarniCvor(operand), _vrednost(vrednost) {}

void VrednostCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_operand << "[" << _vrednost << "]";
}

Funkcija* VrednostCvor::interpretiraj(TablicaSimbola& tablica) const {
    Funkcija* f = _operand->interpretiraj(tablica);
    Funkcija* rez = new KonstantaFunkcija(f->izracunaj(_vrednost)); 
    delete f;

    return rez;
}

IzvodCvor::IzvodCvor(ASTCvor *operand)
    : UnarniCvor(operand) {}

void IzvodCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_operand << "'";
}

Funkcija* IzvodCvor::interpretiraj(TablicaSimbola& tablica) const {
    Funkcija* f = _operand->interpretiraj(tablica); 
    Funkcija* rez = f->izvod();
    // Brisanje isto kao u interaktivnom parseru
    delete f;

    return rez;
}

DodelaCvor::DodelaCvor(const std::string& id, ASTCvor* operand)
    : UnarniCvor(operand), _id(id) {}

void DodelaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _id << " = " << *_operand;
}

Funkcija* DodelaCvor::interpretiraj(TablicaSimbola& tablica) const {
    tablica.dodajFunkciju(_id, _operand->interpretiraj(tablica));
    return nullptr;
}

IspisCvor::IspisCvor(ASTCvor *operand)  
    : UnarniCvor(operand) {}

void IspisCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_operand;
}

Funkcija* IspisCvor::interpretiraj(TablicaSimbola& tablica) const {
    Funkcija* f = _operand->interpretiraj(tablica);
    std::cout << *f << std::endl;
    // Brisanje isto kao u interaktivnom parseru
    delete f;
    
    return nullptr;
}

SinCvor::SinCvor(ASTCvor *operand)
    : UnarniCvor(operand) {}

void SinCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "sin(" << *_operand << ")";
}

Funkcija* SinCvor::interpretiraj(TablicaSimbola& tablica) const {
    return new SinFunkcija(_operand->interpretiraj(tablica));
}

CosCvor::CosCvor(ASTCvor *operand)
    : UnarniCvor(operand) {}

void CosCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "cos(" << *_operand << ")";
}

Funkcija* CosCvor::interpretiraj(TablicaSimbola& tablica) const {
    return new CosFunkcija(_operand->interpretiraj(tablica));
}

//////////////////////////////////////////////////////////////

BinarniCvor::BinarniCvor(ASTCvor *levi, ASTCvor *desni)
    : _levi(levi), _desni(desni) {}

BinarniCvor::~BinarniCvor() {
    delete _levi;
    delete _desni;
}

SabiranjeCvor::SabiranjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void SabiranjeCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "(" << *_levi << ") + (" << *_desni << ")";
}

Funkcija* SabiranjeCvor::interpretiraj(TablicaSimbola& tablica) const {
    return new SabiranjeFunkcija(_levi->interpretiraj(tablica), _desni->interpretiraj(tablica));
}

MnozenjeCvor::MnozenjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void MnozenjeCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "(" << *_levi << ") * (" << *_desni << ")";
}

Funkcija* MnozenjeCvor::interpretiraj(TablicaSimbola& tablica) const {
    return new MnozenjeFunkcija(_levi->interpretiraj(tablica), _desni->interpretiraj(tablica));
}
