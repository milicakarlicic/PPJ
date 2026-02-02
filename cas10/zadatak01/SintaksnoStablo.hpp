#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include <iostream>
#include <vector>
#include "TablicaSimbola.hpp"

class ASTCvor {
public:
    virtual ~ASTCvor() {}
    virtual int interpretiraj(TablicaSimbola& tablica) const = 0;
    virtual void ispisi(std::ostream& izlaz) const = 0;
    virtual ASTCvor* kopija() const = 0;
};

///////////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const ASTCvor& cvor);

///////////////////////////////////////////////

class NizNaredbiCvor : public ASTCvor {
public:
    NizNaredbiCvor();
    NizNaredbiCvor(const NizNaredbiCvor& cvor);
    ~NizNaredbiCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    void dodajNaredbu(ASTCvor* naredba);
    ASTCvor* kopija() const;
private:
    std::vector<ASTCvor*> _naredbe;
};

///////////////////////////////////////////////

class BlokCvor : public ASTCvor {
public:
    BlokCvor(ASTCvor* blok, bool niz);
    BlokCvor(const BlokCvor& cvor);
    ~BlokCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    ASTCvor* _blok;
    bool _niz; // da li je blok niz naredbi ili jedna naredba
};

///////////////////////////////////////////////

class ProgramCvor : public ASTCvor {
public:
    ProgramCvor(ASTCvor* blok);
    ProgramCvor(const ProgramCvor& cvor);
    ~ProgramCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    ASTCvor* _blok;
};

///////////////////////////////////////////////

class DodelaCvor : public ASTCvor {
public:
    DodelaCvor(const std::string& id, ASTCvor* izraz);
    DodelaCvor(const DodelaCvor& cvor);
    ~DodelaCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    std::string _id;
    ASTCvor* _izraz;
};

///////////////////////////////////////////////

class IspisCvor : public ASTCvor {
public:
    IspisCvor(ASTCvor* izraz);
    IspisCvor(const IspisCvor& cvor);
    ~IspisCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    ASTCvor* _izraz;
};

///////////////////////////////////////////////

class KonstantaCvor : public ASTCvor {
public:
    KonstantaCvor(int i);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    int _i;
};

///////////////////////////////////////////////

class PromenljivaCvor : public ASTCvor {
public:
    PromenljivaCvor(const std::string& id);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    std::string _id;
};

///////////////////////////////////////////////

class IfCvor : public ASTCvor {
public:
    IfCvor(ASTCvor* uslov, ASTCvor* blok);
    IfCvor(const IfCvor& cvor);
    ~IfCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    ASTCvor* _uslov;
    ASTCvor* _blok;
};

///////////////////////////////////////////////

class IfElseCvor : public ASTCvor {
public:
    IfElseCvor(ASTCvor* uslov, ASTCvor* ifBlok, ASTCvor* elseBlok);
    IfElseCvor(const IfElseCvor& cvor);
    ~IfElseCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    ASTCvor* _uslov;
    ASTCvor* _ifBlok;
    ASTCvor* _elseBlok;
};

///////////////////////////////////////////////

class WhileCvor : public ASTCvor {
public:
    WhileCvor(ASTCvor* uslov, ASTCvor* blok);
    WhileCvor(const WhileCvor& cvor);
    ~WhileCvor();

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
private:
    ASTCvor* _uslov;
    ASTCvor* _blok;
};

///////////////////////////////////////////////

class BinarnaOperacijaCvor : public ASTCvor {
public:
    BinarnaOperacijaCvor(ASTCvor* levi, ASTCvor* desni);
    BinarnaOperacijaCvor(const BinarnaOperacijaCvor& cvor);
    ~BinarnaOperacijaCvor();
protected:
    ASTCvor* _levi;
    ASTCvor* _desni;
};

class SabiranjeCvor : public BinarnaOperacijaCvor {
public:
    SabiranjeCvor(ASTCvor* levi, ASTCvor* desni);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
};

class OduzimanjeCvor : public BinarnaOperacijaCvor {
public:
    OduzimanjeCvor(ASTCvor* levi, ASTCvor* desni);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
};

class ManjeCvor : public BinarnaOperacijaCvor {
public:
    ManjeCvor(ASTCvor* levi, ASTCvor* desni);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
};

class VeceCvor : public BinarnaOperacijaCvor {
public:
    VeceCvor(ASTCvor* levi, ASTCvor* desni);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
};

class JednakoCvor : public BinarnaOperacijaCvor {
public:
    JednakoCvor(ASTCvor* levi, ASTCvor* desni);

    int interpretiraj(TablicaSimbola& tablica) const;
    void ispisi(std::ostream& izlaz) const;
    ASTCvor* kopija() const;
};

#endif