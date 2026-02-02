#ifndef IZRAZI_HPP
#define IZRAZI_HPP

#include <iostream>
#include <map>
#include <cmath>

////////////////////////////////////////////////

class TablicaSimbola {
private:
    std::map<std::string, double> _promenljive;
public:
    bool dodajPromenljivu(const std::string& id, double vrednost);
    bool definisanaPromenljiva(const std::string& id) const;
    double vrednostPromenljive(const std::string& id) const;
};

////////////////////////////////////////////////

class Izraz {
public:
    virtual ~Izraz() {}
    
    virtual void ispis(std::ostream& izlaz) const = 0;
    virtual double izracunaj(const TablicaSimbola& t) const = 0;
    virtual Izraz* izvod(const std::string& id) const = 0;
    virtual Izraz* kopija() const = 0;
};

////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const Izraz& i);

////////////////////////////////////////////////

class Konstanta : public Izraz {
public:
    Konstanta(double vrednost)
        : _vrednost(vrednost) {}

    void ispis(std::ostream& izlaz) const;
    double izracunaj(const TablicaSimbola& t) const;
    Izraz* izvod(const std::string& prom) const;
    Izraz* kopija() const;
private:
    double _vrednost;
};

class Promenljiva : public Izraz {
public:
    Promenljiva(const std::string& id)
        : _id(id) {}

    void ispis(std::ostream& izlaz) const;
    double izracunaj(const TablicaSimbola& t) const;
    Izraz* izvod(const std::string& prom) const;
    Izraz* kopija() const;
private:
    std::string _id;
};

/////////////////////////////////////////////////

class UnarniIzraz : public Izraz {
public:
    UnarniIzraz(Izraz* operand)
        : _operand(operand) {}
    UnarniIzraz(const UnarniIzraz& izraz) 
        : _operand(izraz._operand->kopija()) {}
    ~UnarniIzraz() {
        delete _operand;
    }
    // Zabrana koriscenja operatora dodele jer ga nismo definisali a podrazumevani nam ne odgovara
    UnarniIzraz& operator=(const UnarniIzraz&) = delete;
protected:
    Izraz *_operand;
};

class Sinus : public UnarniIzraz {
public:
    Sinus(Izraz* operand)
        : UnarniIzraz(operand) {}

    void ispis(std::ostream& izlaz) const;
    double izracunaj(const TablicaSimbola& t) const;
    Izraz* izvod(const std::string& prom) const;
    Izraz* kopija() const;
};

class Kosinus : public UnarniIzraz {
public:
    Kosinus(Izraz* operand)
        : UnarniIzraz(operand) {}

    void ispis(std::ostream& izlaz) const;
    double izracunaj(const TablicaSimbola& t) const;
    Izraz* izvod(const std::string& prom) const;
    Izraz* kopija() const;
};

/////////////////////////////////////////////////

class BinarniIzraz : public Izraz {
public:
    BinarniIzraz(Izraz* levi, Izraz* desni) 
        : _levi(levi), _desni(desni) {}
    BinarniIzraz(const BinarniIzraz& izraz) 
        : _levi(izraz._levi->kopija()), _desni(izraz._desni->kopija()) {}
    ~BinarniIzraz() {
        delete _levi;
        delete _desni;
    }
    // Zabrana koriscenja operatora dodele jer ga nismo definisali a podrazumevani nam ne odgovara
    BinarniIzraz& operator=(const BinarniIzraz&) = delete;
protected:
    Izraz* _levi;
    Izraz* _desni;
};

class Sabiranje : public BinarniIzraz {
public:
    Sabiranje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    void ispis(std::ostream& izlaz) const;
    double izracunaj(const TablicaSimbola& t) const;
    Izraz* izvod(const std::string& prom) const;
    Izraz* kopija() const;
};

class Mnozenje : public BinarniIzraz {
public:
    Mnozenje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
        
    void ispis(std::ostream& izlaz) const;
    double izracunaj(const TablicaSimbola& t) const;
    Izraz* izvod(const std::string& prom) const;
    Izraz* kopija() const;
};
 
#endif