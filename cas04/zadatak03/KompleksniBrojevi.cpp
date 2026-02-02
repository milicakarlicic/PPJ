#include "KompleksniBrojevi.h"

KompleksanBroj::KompleksanBroj(double realni, double imaginarni) 
    : _realni(realni), _imaginarni(imaginarni) {}

void KompleksanBroj::ispisi(std::ostream& izlaz) const {
    std::string znak = _imaginarni >= 0 ? " + " : " - ";
    izlaz << _realni << znak << fabs(_imaginarni) << "i";
}

void KompleksanBroj::ucitaj(std::istream& ulaz) {
    ulaz >> _realni >> _imaginarni;
}

KompleksanBroj KompleksanBroj::operator+(const KompleksanBroj& z) const {
    return KompleksanBroj(_realni + z._realni, _imaginarni + z._imaginarni);
}

KompleksanBroj KompleksanBroj::operator/(const KompleksanBroj& z) const {
    // (a+bi) / (c+di) | * (c-di)
    if (z == KompleksanBroj(0, 0)) {
        throw "Nula nema inverz!";
    }
    double konst = z._realni * z._realni + z._imaginarni * z._imaginarni;
    double realni = _realni * z._realni + _imaginarni * z._imaginarni;
    double imaginarni = - _realni * z._imaginarni + _imaginarni * z._realni;

    return KompleksanBroj(realni / konst, imaginarni / konst);
}

bool KompleksanBroj::operator==(const KompleksanBroj& z) const {
    return _realni == z._realni && _imaginarni == z._imaginarni;
}

std::ostream& operator<<(std::ostream& izlaz, const KompleksanBroj& z) {
    z.ispisi(izlaz);
    return izlaz;
}

std::istream& operator>>(std::istream& ulaz, KompleksanBroj& z) {
    std::cout << "Unesi kompleksan broj bez razmaka u formatu: a+bi" << std::endl;
    z.ucitaj(ulaz); 

    return ulaz;
}