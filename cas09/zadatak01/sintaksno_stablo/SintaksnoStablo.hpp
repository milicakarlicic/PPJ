#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include <iostream>
#include <vector>
#include "Funkcije.hpp"
#include "TablicaSimbola.hpp"

///////////////////////////////////////////

class ASTCvor {
public:
    virtual ~ASTCvor() {}

    virtual void ispisi(std::ostream& izlaz) const = 0;
    virtual Funkcija* interpretiraj(TablicaSimbola& tablica) const = 0;
};

///////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const ASTCvor& cvor);

///////////////////////////////////////////

class NizNaredbiCvor : public ASTCvor {
public:
    ~NizNaredbiCvor();

    void dodajNaredbu(ASTCvor* naredba);
    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    std::vector<ASTCvor*> _naredbe;
};

///////////////////////////////////////////

class KonstantaCvor : public ASTCvor {
public:
    KonstantaCvor(double vrednost);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    double _vrednost;
};

///////////////////////////////////////////

class IdentitetCvor : public ASTCvor {
public:
    IdentitetCvor();

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

///////////////////////////////////////////

class PromenljivaCvor : public ASTCvor {
public:
    PromenljivaCvor(const std::string &id);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    std::string _id;
};

///////////////////////////////////////////

class PrazanCvor : public ASTCvor {
public: 
    PrazanCvor();

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

///////////////////////////////////////////

class UnarniCvor : public ASTCvor {
public:
    UnarniCvor(ASTCvor* operand);
    ~UnarniCvor();
protected:
    ASTCvor* _operand;
};

class IspisCvor : public UnarniCvor {
public:
    IspisCvor(ASTCvor* operand);
    
    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

class DodelaCvor : public UnarniCvor {
public:
    DodelaCvor(const std::string& id, ASTCvor* operand);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    std::string _id;
};

class VrednostCvor : public UnarniCvor {
public: 
    VrednostCvor(ASTCvor* operand, double vrednost);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    double _vrednost;
};


class SinCvor : public UnarniCvor {
public:
    SinCvor(ASTCvor* operand);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    std::string _id;
};

class CosCvor : public UnarniCvor {
public:
    CosCvor(ASTCvor* operand);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    std::string _id;
};

class UnMinusCvor : public UnarniCvor {
public:
    UnMinusCvor(ASTCvor* operand);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

class IzvodCvor : public UnarniCvor {
public:
    IzvodCvor(ASTCvor* operand);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

class KompozicijaCvor : public UnarniCvor {
public:
    KompozicijaCvor(const std::string& id, ASTCvor* operand);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
private:
    std::string _id;
};

///////////////////////////////////////////

class BinarniCvor : public ASTCvor {
public:
    BinarniCvor(ASTCvor* levi, ASTCvor* desni);
    ~BinarniCvor();
protected:
    ASTCvor* _levi;
    ASTCvor* _desni;
};

class SabiranjeCvor : public BinarniCvor {
public:
    SabiranjeCvor(ASTCvor* levi, ASTCvor* desni);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

class OduzimanjeCvor : public BinarniCvor {
public:
    OduzimanjeCvor(ASTCvor* levi, ASTCvor* desni);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

class MnozenjeCvor : public BinarniCvor {
public:
    MnozenjeCvor(ASTCvor* levi, ASTCvor* desni);

    void ispisi(std::ostream& izlaz) const;
    Funkcija* interpretiraj(TablicaSimbola& tablica) const;
};

#endif