#include "SintaksnoStablo.hpp"

//////////////////////////////////////////

void TablicaSimbola::dodajPromenljivu(const std::string& id, double vrednost) {
    _promenljive[id] = vrednost;
}

double TablicaSimbola::vratiVrednost(const std::string& id) const {
    auto it = _promenljive.find(id);
    if (it == _promenljive.end()) {
        throw "promenljiva nije definisana";
    }
    return it->second;
}

bool TablicaSimbola::postojiVrednost(const std::string& id) const {
    return _promenljive.find(id) != _promenljive.end();
}

//////////////////////////////////////////

std::ostream& operator << (std::ostream& izlaz, const ASTCvor& cvor) {
    cvor.ispisi(izlaz);
    return izlaz;
}

//////////////////////////////////////////

Konstanta::Konstanta(double vrednost)
    : _vrednost(vrednost) {}

void Konstanta::ispisi(std::ostream& izlaz) const {
    izlaz << _vrednost;
}

double Konstanta::interpretiraj(TablicaSimbola& tablica) const {
    return _vrednost;
}

ASTCvor* Konstanta::kopija() const {
    return new Konstanta(*this);
}

//////////////////////////////////////////

Promenljiva::Promenljiva(const std::string& id)
    : _id(id) {}

void Promenljiva::ispisi(std::ostream& izlaz) const {
    izlaz << _id;
}

double Promenljiva::interpretiraj(TablicaSimbola& tablica) const {
    double vrednost;
    try {
        vrednost = tablica.vratiVrednost(_id);
    } catch (const char *poruka) {
        std::cerr << poruka << std:: endl;
        exit(EXIT_FAILURE);
    }
    return vrednost;
}

ASTCvor* Promenljiva::kopija() const {
    return new Promenljiva(*this);
}

//////////////////////////////////////////

NizNaredbi::NizNaredbi() {}

NizNaredbi::NizNaredbi(const std::vector<ASTCvor*>& naredbe) 
    : _naredbe(naredbe) {}

NizNaredbi::NizNaredbi(const NizNaredbi& n) {
    for (auto it = n._naredbe.begin(); it != n._naredbe.end(); it++) {
        _naredbe.push_back((*it)->kopija());
    }
}

NizNaredbi::~NizNaredbi() {
    for (ASTCvor* naredba : _naredbe) {
        delete naredba;
    }
}

void NizNaredbi::ispisi(std::ostream& izlaz) const {
    for (ASTCvor *naredba : _naredbe) {
        izlaz << *naredba << std::endl;
    }
}

void NizNaredbi::dodajNaredbu(ASTCvor* naredba) {
    _naredbe.push_back(naredba);
}

double NizNaredbi::interpretiraj(TablicaSimbola& tablica) const {
    for (ASTCvor *naredba : _naredbe) {
        naredba->interpretiraj(tablica);
    }
    return 0;
}

ASTCvor* NizNaredbi::kopija() const {
    return new NizNaredbi(*this);
}

//////////////////////////////////////////

BinarniCvor::BinarniCvor(ASTCvor* levi, ASTCvor* desni)
    : _levi(levi), _desni(desni) {}

BinarniCvor::BinarniCvor(const BinarniCvor& cvor) {
    _levi = cvor._levi->kopija();
    _desni = cvor._desni->kopija();
}

BinarniCvor::~BinarniCvor() {
    delete _levi;
    delete _desni;
}

Sabiranje::Sabiranje(ASTCvor* levi, ASTCvor* desni)
    : BinarniCvor(levi, desni) {}

void Sabiranje::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " + " << *_desni;
}

double Sabiranje::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) + _desni->interpretiraj(tablica);
}

ASTCvor* Sabiranje::kopija() const {
    return new Sabiranje(*this);
}

Mnozenje::Mnozenje(ASTCvor* levi, ASTCvor* desni)
    : BinarniCvor(levi, desni) {}

void Mnozenje::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " * " << *_desni;
}

double Mnozenje::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) * _desni->interpretiraj(tablica);
}

ASTCvor* Mnozenje::kopija() const {
    return new Mnozenje(*this);
}

Jednako::Jednako(ASTCvor* levi, ASTCvor* desni)
    : BinarniCvor(levi, desni) {}

void Jednako::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " == " << *_desni;
}

double Jednako::interpretiraj(TablicaSimbola& tablica) const {
    bool rezultat = _levi->interpretiraj(tablica) == _desni->interpretiraj(tablica);
    std::cout << (rezultat ? "true" : "false") << std::endl;
    return rezultat;
}

ASTCvor* Jednako::kopija() const {
    return new Jednako(*this);
}

///////////////////////////////////////////

UnarniCvor::UnarniCvor(ASTCvor* operand) 
    : _operand(operand) {}

UnarniCvor::UnarniCvor(const UnarniCvor& cvor) {
    _operand = cvor._operand->kopija();
}

UnarniCvor::~UnarniCvor() {
    delete _operand;
}

// Definicija
Definicija::Definicija(const std::string& id, ASTCvor* operand)
    : UnarniCvor(operand), _id(id) {}

void Definicija::ispisi(std::ostream& izlaz) const {
    izlaz << "def " << _id << " = " << *_operand;
}

double Definicija::interpretiraj(TablicaSimbola& tablica) const {
    if (tablica.postojiVrednost(_id)) {
        std::cerr << "Promenljiva vec definisana!" << std::endl;
        exit(EXIT_FAILURE);
    }
    tablica.dodajPromenljivu(_id, _operand->interpretiraj(tablica));

    return 0;
}

ASTCvor* Definicija::kopija() const {
    return new Definicija(*this);
}

// Dodela
Dodela::Dodela(const std::string& id, ASTCvor* operand)
    : UnarniCvor(operand), _id(id) {}

void Dodela::ispisi(std::ostream& izlaz) const {
    izlaz << _id << " = " << *_operand;
}

double Dodela::interpretiraj(TablicaSimbola& tablica) const {
    if (!tablica.postojiVrednost(_id)) {
        std::cerr << "Promenljiva nije definisana!" << std::endl;
        exit(EXIT_FAILURE);
    }
    tablica.dodajPromenljivu(_id, _operand->interpretiraj(tablica));

    return 0;
}

ASTCvor* Dodela::kopija() const {
    return new Dodela(*this);
}

// Ispis
Ispis::Ispis(ASTCvor* operand)
    : UnarniCvor(operand) {}

void Ispis::ispisi(std::ostream& izlaz) const {
    izlaz << "print(" << *_operand << ")";
}

double Ispis::interpretiraj(TablicaSimbola& tablica) const {
    std::cout << _operand->interpretiraj(tablica) << std::endl;

    return 0;
}

ASTCvor* Ispis::kopija() const {
    return new Ispis(*this);
}

// Negacija
Negacija::Negacija(ASTCvor* operand)
    : UnarniCvor(operand) {}

void Negacija::ispisi(std::ostream& izlaz) const {
    izlaz << "-" << *_operand;
}

double Negacija::interpretiraj(TablicaSimbola& tablica) const {
    return - _operand->interpretiraj(tablica);
}

ASTCvor* Negacija::kopija() const {
    return new Negacija(*this);
}