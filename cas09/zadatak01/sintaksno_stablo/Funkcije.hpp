#ifndef FUNKCIJE_HPP
#define FUNKCIJE_HPP

#include <iostream>

////////////////////////////////////////

class Funkcija {
public:
    virtual ~Funkcija() {}

    virtual void ispisi(std::ostream& izlaz) const = 0;
    virtual double izracunaj(double vrednost) const = 0;
    virtual Funkcija* kompozicija(Funkcija* f) const = 0;
    virtual Funkcija* izvod() const = 0;
    virtual Funkcija* kopija() const = 0;
};

////////////////////////////////////////

std::ostream& operator<<(std::ostream& izlaz, const Funkcija& f);

////////////////////////////////////////

class KonstantaFunkcija : public Funkcija {
public:
    KonstantaFunkcija(double vrednost);

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
private:
    double _vrednost;
};

////////////////////////////////////////

class IdentitetFunkcija : public Funkcija {
public:
    IdentitetFunkcija();

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

////////////////////////////////////////

class UnarnaFunkcija : public Funkcija {
public:
    UnarnaFunkcija(Funkcija* operand);
    UnarnaFunkcija(const UnarnaFunkcija& f);
    ~UnarnaFunkcija();
protected:
    Funkcija* _operand;
};

class SinFunkcija : public UnarnaFunkcija {
public:
    SinFunkcija(Funkcija* operand);

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

class CosFunkcija : public UnarnaFunkcija {
public:
    CosFunkcija(Funkcija* operand);

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

class UnMinusFunkcija : public UnarnaFunkcija {
public:
    UnMinusFunkcija(Funkcija* operand);

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

////////////////////////////////////////

class BinarnaFunkcija : public Funkcija {
public:
    BinarnaFunkcija(Funkcija* levi, Funkcija* desni);
    BinarnaFunkcija(const BinarnaFunkcija& f);
    ~BinarnaFunkcija();
protected:
    Funkcija* _levi;
    Funkcija* _desni;
};

class SabiranjeFunkcija : public BinarnaFunkcija {
public:
    SabiranjeFunkcija(Funkcija* levi, Funkcija* desni);

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

class OduzimanjeFunkcija : public BinarnaFunkcija {
public:
    OduzimanjeFunkcija(Funkcija* levi, Funkcija* desni);

    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

class MnozenjeFunkcija : public BinarnaFunkcija {
public:
    MnozenjeFunkcija(Funkcija* levi, Funkcija* desni);
    
    void ispisi(std::ostream& izlaz) const;
    double izracunaj(double vrednost) const;
    Funkcija* kompozicija(Funkcija* f) const;
    Funkcija* izvod() const;
    Funkcija* kopija() const;
};

#endif