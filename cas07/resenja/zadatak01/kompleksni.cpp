#include <iostream>
#include <cmath>
#include "kompleksni.hpp"

KompleksanBroj::KompleksanBroj(double realni, double imaginarni) 
    : m_realni(realni), m_imaginarni(imaginarni) { }

void KompleksanBroj::ispisi(std::ostream& izlaz) const {
    izlaz << m_realni;
    if (m_imaginarni != 0) {
        std::string znak = (m_imaginarni > 0) ? "+" : "-";
        izlaz << znak << fabs(m_imaginarni) << "i";
    }
}

void KompleksanBroj::setImaginarni(double imaginarni) {
    m_imaginarni = imaginarni;
}

KompleksanBroj KompleksanBroj::operator+(const KompleksanBroj& z) const {
    return KompleksanBroj(m_realni + z.m_realni, m_imaginarni + z.m_imaginarni);
}

KompleksanBroj KompleksanBroj::operator/(const KompleksanBroj& z) const {
    // (a + bi) / (c + di)  | * (c - di)
    // ((ac + bd) + (-ad + bc)i) / (c^2 + d^2)
    double realni = m_realni * z.m_realni + m_imaginarni * z.m_imaginarni;
    double imaginarni = - m_realni * z.m_imaginarni + m_imaginarni * z.m_realni;

    double konst = pow(z.m_realni, 2) + pow(z.m_imaginarni, 2);
    if (konst == 0) {
        throw "Deljenje sa nulom!";
    }

    return KompleksanBroj(realni / konst, imaginarni / konst);
}

bool KompleksanBroj::operator==(const KompleksanBroj& z) const {
    return m_realni == z.m_realni && m_imaginarni == z.m_imaginarni;
}

std::ostream& operator<<(std::ostream& izlaz, const KompleksanBroj& z) {
    z.ispisi(izlaz);
    return izlaz;
}

std::istream& operator>>(std::istream& ulaz, KompleksanBroj& z) {
    double realni, imaginarni;
    ulaz >> realni >> imaginarni;
    z = KompleksanBroj(realni, imaginarni);

    return ulaz;
}
