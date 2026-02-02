#include "SintaksnoStablo.hpp"

///////////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const ASTCvor& cvor) {
    cvor.ispisi(izlaz);
    return izlaz;
}

///////////////////////////////////////////////

ProgramCvor::ProgramCvor(ASTCvor* blok)
    : _blok(blok) {}

ProgramCvor::ProgramCvor(const ProgramCvor& cvor) {
    _blok = cvor._blok->kopija();
}

ProgramCvor::~ProgramCvor() {
    delete _blok;
}

int ProgramCvor::interpretiraj(TablicaSimbola& tablica) const {
    _blok->interpretiraj(tablica);
    return 0;
}

void ProgramCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "begin\n";
    izlaz << *_blok;
    izlaz << "end.\n";
}

ASTCvor* ProgramCvor::kopija() const {
    return new ProgramCvor(*this);
}

///////////////////////////////////////////////

NizNaredbiCvor::NizNaredbiCvor() {}

NizNaredbiCvor::NizNaredbiCvor(const NizNaredbiCvor& cvor) {
    _naredbe.resize(cvor._naredbe.size());
    for (int i = 0; i < cvor._naredbe.size(); i++) {
        _naredbe[i] = cvor._naredbe[i]->kopija();
    }
}

NizNaredbiCvor::~NizNaredbiCvor() {
    for (auto naredba : _naredbe) {
        delete naredba;
    }
}

int NizNaredbiCvor::interpretiraj(TablicaSimbola& tablica) const {
    for (ASTCvor* naredba : _naredbe) {
        naredba->interpretiraj(tablica);
    }
    return 0;
}

void NizNaredbiCvor::ispisi(std::ostream& izlaz) const {
    for (ASTCvor* naredba : _naredbe) {
        izlaz << *naredba << std::endl;
    }
}

void NizNaredbiCvor::dodajNaredbu(ASTCvor* naredba) {
    _naredbe.push_back(naredba);
}

ASTCvor* NizNaredbiCvor::kopija() const {
    return new NizNaredbiCvor(*this);
}
///////////////////////////////////////////////

BlokCvor::BlokCvor(ASTCvor* blok, bool niz)
    : _blok(blok), _niz(niz) {}

BlokCvor::BlokCvor(const BlokCvor& cvor)
    : _niz(cvor._niz) {
    _blok = cvor._blok->kopija();
}

BlokCvor::~BlokCvor() {
    delete _blok;
}

int BlokCvor::interpretiraj(TablicaSimbola& tablica) const {
    _blok->interpretiraj(tablica);
    return 0;
}

void BlokCvor::ispisi(std::ostream& izlaz) const {
    if (_niz) {
        izlaz << "begin\n";
        izlaz << *_blok;
        izlaz << "end\n";
    } else {
        izlaz << *_blok;
    }
}

ASTCvor* BlokCvor::kopija() const {
    return new BlokCvor(_blok->kopija(), _niz);
}

///////////////////////////////////////////////

DodelaCvor::DodelaCvor(const std::string& id, ASTCvor* izraz)
    : _id(id), _izraz(izraz) {}

DodelaCvor::DodelaCvor(const DodelaCvor& cvor)
    : _id(cvor._id) {
    _izraz = cvor._izraz->kopija();
}

DodelaCvor::~DodelaCvor() {
    delete _izraz;
}

int DodelaCvor::interpretiraj(TablicaSimbola& tablica) const {
    tablica.dodajPromenljivu(_id, _izraz->interpretiraj(tablica));
    return 0;
}

void DodelaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _id << " := " << *_izraz << ";";
}

ASTCvor* DodelaCvor::kopija() const {
    return new DodelaCvor(_id, _izraz->kopija());
}

///////////////////////////////////////////////

IspisCvor::IspisCvor(ASTCvor* izraz)
    : _izraz(izraz) {}

IspisCvor::IspisCvor(const IspisCvor& cvor) {
    _izraz = cvor._izraz->kopija();
}

IspisCvor::~IspisCvor() {
    delete _izraz;
}

int IspisCvor::interpretiraj(TablicaSimbola& tablica) const {
    std::cout << _izraz->interpretiraj(tablica) << std::endl;
    return 0;
}

void IspisCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "print(" << *_izraz << ");";
}

ASTCvor* IspisCvor::kopija() const {
    return new IspisCvor(_izraz->kopija());
}

///////////////////////////////////////////////

KonstantaCvor::KonstantaCvor(int i)
    : _i(i) {}

int KonstantaCvor::interpretiraj(TablicaSimbola& tablica) const {
    return _i;
}

void KonstantaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _i;
}

ASTCvor* KonstantaCvor::kopija() const {
    return new KonstantaCvor(*this);
}

///////////////////////////////////////////////

PromenljivaCvor::PromenljivaCvor(const std::string& id)
    : _id(id) {}

int PromenljivaCvor::interpretiraj(TablicaSimbola& tablica) const {
    return tablica.vratiVrednost(_id);
}

void PromenljivaCvor::ispisi(std::ostream& izlaz) const {
    izlaz << _id;
}

ASTCvor* PromenljivaCvor::kopija() const {
    return new PromenljivaCvor(*this);
}

///////////////////////////////////////////////

IfCvor::IfCvor(ASTCvor* uslov, ASTCvor* blok)
    : _uslov(uslov), _blok(blok) {}

IfCvor::IfCvor(const IfCvor& cvor) {
    _uslov = cvor._uslov->kopija();
    _blok = cvor._blok->kopija();
}

IfCvor::~IfCvor() {
    delete _uslov;
    delete _blok;
}

int IfCvor::interpretiraj(TablicaSimbola& tablica) const {
    if (_uslov->interpretiraj(tablica)) {
        _blok->interpretiraj(tablica);
    }
    return 0;
}

void IfCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "if " << *_uslov << " then\n" << *_blok;
}

ASTCvor* IfCvor::kopija() const {
    return new IfCvor(*this);
}

///////////////////////////////////////////////

IfElseCvor::IfElseCvor(ASTCvor* uslov, ASTCvor* ifBlok, ASTCvor* elseBlok)
    : _uslov(uslov), _ifBlok(ifBlok), _elseBlok(elseBlok) {}

IfElseCvor::IfElseCvor(const IfElseCvor& cvor) {
    _uslov = cvor._uslov->kopija();
    _ifBlok = cvor._ifBlok->kopija();
    _elseBlok = cvor._elseBlok->kopija();
}

IfElseCvor::~IfElseCvor() {
    delete _uslov;
    delete _ifBlok;
    delete _elseBlok;
}

int IfElseCvor::interpretiraj(TablicaSimbola& tablica) const {
    if (_uslov->interpretiraj(tablica)) {
        _ifBlok->interpretiraj(tablica);
    } else {
        _elseBlok->interpretiraj(tablica);
    }
    return 0;
}

void IfElseCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "if " << *_uslov << " then\n" << *_ifBlok << "\n";
    izlaz << "else\n" << *_elseBlok;
}

ASTCvor* IfElseCvor::kopija() const {
    return new IfElseCvor(*this);
}

///////////////////////////////////////////////

WhileCvor::WhileCvor(ASTCvor* uslov, ASTCvor* blok)
    : _uslov(uslov), _blok(blok) {}

WhileCvor::WhileCvor(const WhileCvor& cvor) {
    _uslov = cvor._uslov->kopija();
    _blok = cvor._blok->kopija();
}

WhileCvor::~WhileCvor() {
    delete _uslov;
    delete _blok;
}

int WhileCvor::interpretiraj(TablicaSimbola& tablica) const {
    while (_uslov->interpretiraj(tablica)) {
        _blok->interpretiraj(tablica);
    }
    return 0;
}

void WhileCvor::ispisi(std::ostream& izlaz) const {
    izlaz << "while " << *_uslov << " do\n" << *_blok;
}

ASTCvor* WhileCvor::kopija() const {
    return new WhileCvor(*this);
}

///////////////////////////////////////////////

BinarnaOperacijaCvor::BinarnaOperacijaCvor(ASTCvor* levi, ASTCvor* desni)
    : _levi(levi), _desni(desni) {}

BinarnaOperacijaCvor::BinarnaOperacijaCvor(const BinarnaOperacijaCvor& cvor) {
    _levi = cvor._levi->kopija();
    _desni = cvor._desni->kopija();
}

BinarnaOperacijaCvor::~BinarnaOperacijaCvor() {
    delete _levi;
    delete _desni;
}

SabiranjeCvor::SabiranjeCvor(ASTCvor* levi, ASTCvor* desni)
    : BinarnaOperacijaCvor(levi, desni) {}

int SabiranjeCvor::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) + _desni->interpretiraj(tablica);
}

void SabiranjeCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " + " << *_desni;
}

ASTCvor* SabiranjeCvor::kopija() const {
    return new SabiranjeCvor(*this);
}

OduzimanjeCvor::OduzimanjeCvor(ASTCvor* levi, ASTCvor* desni)
    : BinarnaOperacijaCvor(levi, desni) {}

int OduzimanjeCvor::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) - _desni->interpretiraj(tablica);
}

void OduzimanjeCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " - " << *_desni;
}

ASTCvor* OduzimanjeCvor::kopija() const {
    return new OduzimanjeCvor(*this);
}

ManjeCvor::ManjeCvor(ASTCvor* levi, ASTCvor* desni)
    : BinarnaOperacijaCvor(levi, desni) {}


int ManjeCvor::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) < _desni->interpretiraj(tablica);
}

void ManjeCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " < " << *_desni;
}

ASTCvor* ManjeCvor::kopija() const {
    return new ManjeCvor(*this);
}

VeceCvor::VeceCvor(ASTCvor* levi, ASTCvor* desni)
    : BinarnaOperacijaCvor(levi, desni) {}

int VeceCvor::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) > _desni->interpretiraj(tablica);
}

void VeceCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " > " << *_desni;
}

ASTCvor* VeceCvor::kopija() const {
    return new VeceCvor(*this);
}

JednakoCvor::JednakoCvor(ASTCvor* levi, ASTCvor* desni)
    : BinarnaOperacijaCvor(levi, desni) {}

int JednakoCvor::interpretiraj(TablicaSimbola& tablica) const {
    return _levi->interpretiraj(tablica) == _desni->interpretiraj(tablica);
}

void JednakoCvor::ispisi(std::ostream& izlaz) const {
    izlaz << *_levi << " == " << *_desni;
}

ASTCvor* JednakoCvor::kopija() const {
    return new JednakoCvor(*this);
}