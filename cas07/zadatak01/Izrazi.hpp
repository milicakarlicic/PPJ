#ifndef IZRAZI_HPP
#define IZRAZI_HPP

#include <iostream>
#include <map>
#include <cmath>

class TablicaSimbola {
private:
    std::map<std::string, double> promenljive;
public:
    bool dodajPromenljivu(const std::string &naziv, double vrednost);
    bool definisanaPromenljiva(const std::string &naziv) const;
    double vrednostPromenljive(const std::string &naziv) const;
};

////////////////////////////////////////////////

class Izraz {
public:
    virtual ~Izraz() {}
    virtual void ispis(std::ostream &izlaz) const = 0;
    virtual double izracunaj(const TablicaSimbola &t) const = 0;
    virtual Izraz* izvod(const std::string &naziv) const = 0;
    virtual Izraz* kopija() const = 0;
};

////////////////////////////////////////////////

std::ostream& operator << (std::ostream &izlaz, const Izraz &i);

class Konstanta : public Izraz {
private:
    double _vrednost;
public:
    Konstanta(double vrednost)
        : _vrednost(vrednost) {}
    virtual void ispis(std::ostream &izlaz) const;
    virtual double izracunaj(const TablicaSimbola &t) const;
    virtual Izraz* izvod(const std::string &naziv) const;
    virtual Izraz* kopija() const;
};

class Promenljiva : public Izraz {
private:
    std::string _naziv;
public:
    Promenljiva(const std::string &naziv)
        : _naziv(naziv) {}
    virtual void ispis(std::ostream &izlaz) const;
    virtual double izracunaj(const TablicaSimbola &t) const;
    virtual Izraz* izvod(const std::string &naziv) const;
    virtual Izraz* kopija() const;
};

/////////////////////////////////////////////////

class UnarniIzraz : public Izraz {
protected:
    Izraz *_operand;
public:
    UnarniIzraz(Izraz *operand)
        : _operand(operand) {}
    UnarniIzraz(const UnarniIzraz &izraz) 
        : _operand(izraz._operand->kopija()) {}
    ~UnarniIzraz() {
        delete _operand;
    }
    // Zabrana koriscenja operatora dodele jer ga nismo definisali a podrazumevani nam ne odgovara
    UnarniIzraz& operator = (const UnarniIzraz&) = delete;
};

class Sinus : public UnarniIzraz {
public:
    Sinus(Izraz *operand)
        : UnarniIzraz(operand) {}
    virtual void ispis(std::ostream &izlaz) const;
    virtual double izracunaj(const TablicaSimbola &t) const;
    virtual Izraz* izvod(const std::string &naziv) const;
    virtual Izraz* kopija() const;
};

class Kosinus : public UnarniIzraz {
public:
    Kosinus(Izraz *operand)
        : UnarniIzraz(operand) {}
    virtual void ispis(std::ostream &izlaz) const;
    virtual double izracunaj(const TablicaSimbola &t) const;
    virtual Izraz* izvod(const std::string &naziv) const;
    virtual Izraz* kopija() const;
};

/////////////////////////////////////////////////

class BinarniIzraz : public Izraz {
protected:
    Izraz *_levi;
    Izraz *_desni;
public:
    BinarniIzraz(Izraz *levi, Izraz *desni) 
        : _levi(levi), _desni(desni) {}
    BinarniIzraz(const BinarniIzraz &izraz) 
        : _levi(izraz._levi->kopija()), _desni(izraz._desni->kopija()) {}
    ~BinarniIzraz() {
        delete _levi;
        delete _desni;
    }
    // Zabrana koriscenja operatora dodele jer ga nismo definisali a podrazumevani nam ne odgovara
    BinarniIzraz& operator = (const BinarniIzraz&) = delete;
};

class Zbir : public BinarniIzraz {
public:
    Zbir(Izraz *levi, Izraz *desni)
        : BinarniIzraz(levi, desni) {}
    virtual void ispis(std::ostream &izlaz) const;
    virtual double izracunaj(const TablicaSimbola &t) const;
    virtual Izraz* izvod(const std::string &naziv) const;
    virtual Izraz* kopija() const;
};

class Proizvod : public BinarniIzraz {
public:
    Proizvod(Izraz *levi, Izraz *desni)
        : BinarniIzraz(levi, desni) {}
    virtual void ispis(std::ostream &izlaz) const;
    virtual double izracunaj(const TablicaSimbola &t) const;
    virtual Izraz* izvod(const std::string &naziv) const;
    virtual Izraz* kopija() const;
};
 
#endif