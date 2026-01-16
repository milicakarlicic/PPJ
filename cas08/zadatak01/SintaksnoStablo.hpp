#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include <iostream>
#include <vector>
#include <map>

//////////////////////////////////////////

class TablicaSimbola {
public:
    void dodajPromenljivu(const std::string &id, double vrednost);
    double vratiVrednost(const std::string &id) const;
    bool postojiVrednost(const std::string &id) const;
private:
    std::map<std::string, double> _promenljive;
};

//////////////////////////////////////////

class ASTCvor {
public:
    virtual ~ASTCvor() {}

    virtual void ispisi(std::ostream &izlaz) const = 0;
    virtual double interpretiraj(TablicaSimbola &tablica) const = 0;
    virtual ASTCvor* kopija() const = 0;
};

/////////////////////////////////////////

std::ostream& operator << (std::ostream &izlaz, const ASTCvor &cvor);

/////////////////////////////////////////

class Konstanta : public ASTCvor {
public:
    Konstanta(double vrednost);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
private:
    double _vrednost;
};

/////////////////////////////////////////

class Promenljiva : public ASTCvor {
public:
    Promenljiva(const std::string &id);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
private:
    std::string _id;
};

/////////////////////////////////////////

class NizNaredbi : public ASTCvor {
public:
    NizNaredbi();
    NizNaredbi(const std::vector<ASTCvor*> &naredbe);
    NizNaredbi(const NizNaredbi &n);
    ~NizNaredbi();

    void ispisi(std::ostream &izlaz) const;
    void dodajNaredbu(ASTCvor *naredba);
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
private:
    std::vector<ASTCvor*> _naredbe;
};

/////////////////////////////////////////

class BinarniCvor : public ASTCvor {
public:
    BinarniCvor(ASTCvor *levi, ASTCvor *desni);
    BinarniCvor(const BinarniCvor &cvor);
    ~BinarniCvor();
protected:
    ASTCvor *_levi;
    ASTCvor *_desni;
};

class Zbir : public BinarniCvor {
public:
    Zbir(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
};

class Proizvod : public BinarniCvor {
public:
    Proizvod(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
};

class Jednako : public BinarniCvor {
public:
    Jednako(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
};

/////////////////////////////////////////

class UnarniCvor : public ASTCvor {
public:
    UnarniCvor(ASTCvor *operand);
    UnarniCvor(const UnarniCvor &cvor);
    ~UnarniCvor();
protected:
    ASTCvor *_operand;
};

class Definicija : public UnarniCvor {
public:
    Definicija(const std::string &id, ASTCvor *operand);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
private:
    std::string _id;
};

class Dodela : public UnarniCvor {
public:
    Dodela(const std::string &id, ASTCvor *operand);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
private:
    std::string _id;
};

class Ispis : public UnarniCvor {
public:
    Ispis(ASTCvor *operand);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
};

class Negacija : public UnarniCvor {
public:
    Negacija(ASTCvor *operand);

    void ispisi(std::ostream &izlaz) const;
    double interpretiraj(TablicaSimbola &tablica) const;
    ASTCvor* kopija() const;
};

#endif