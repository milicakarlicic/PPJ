#include "dinamicki_niz.hpp"

DinamickiNiz::DinamickiNiz() {
    m_elementi = new double[INICIJALNI_KAPACITET];
    m_brojElemenata = 0;
    m_kapacitet = INICIJALNI_KAPACITET;
}

DinamickiNiz::DinamickiNiz(const DinamickiNiz& niz) {
    m_kapacitet = niz.m_kapacitet;
    m_brojElemenata = niz.m_brojElemenata;
    m_elementi = new double[m_kapacitet];

    for (int i = 0; i < m_brojElemenata; i++) {
        m_elementi[i] = niz.m_elementi[i];
    }
}

DinamickiNiz::~DinamickiNiz() {
    delete[] m_elementi;
}

DinamickiNiz& DinamickiNiz::operator=(const DinamickiNiz& niz) {
    if (this == &niz) {
        return *this;
    }

    double* pomNiz = new double[niz.m_kapacitet];

    for (int i = 0; i < niz.m_brojElemenata; i++) {
        pomNiz[i] = niz.m_elementi[i];
    }

    delete[] m_elementi;

    m_elementi = pomNiz;
    m_kapacitet = niz.m_kapacitet;
    m_brojElemenata = niz.m_brojElemenata;

    return *this;
}

void DinamickiNiz::dodaj(double element) {
    if (m_kapacitet == m_brojElemenata) {
        m_kapacitet *= 2;

        double* pomNiz = new double[m_kapacitet];
        for (int i = 0; i < m_brojElemenata; i++) {
            pomNiz[i] = m_elementi[i];
        }

        delete[] m_elementi;
        m_elementi = pomNiz;
    }

    m_elementi[m_brojElemenata++] = element;
}

double& DinamickiNiz::operator[](int indeks) {
    if (indeks < 0 || indeks >= m_brojElemenata) {
        throw "Nevalidan indeks!";
    }

    return m_elementi[indeks];
}

void DinamickiNiz::ispisi(std::ostream& izlaz) const {
    for (int i = 0; i < m_brojElemenata; i++) {
        izlaz << m_elementi[i] << " ";
    }
}

std::ostream& operator<<(std::ostream& izlaz, const DinamickiNiz& niz) {
    niz.ispisi(izlaz);
    return izlaz;
}
