#ifndef KOMPLEKSNI_HPP
#define KOMPLEKSNI_HPP

class KompleksanBroj {
public:
    KompleksanBroj(double realni = 0, double imaginarni = 0);

    void setImaginarni(double imaginarni);
    void ispisi(std::ostream& izlaz) const;

    KompleksanBroj operator+(const KompleksanBroj& z) const;
    KompleksanBroj operator/(const KompleksanBroj& z) const;
    bool operator==(const KompleksanBroj& z) const;
private:
    double m_realni;
    double m_imaginarni;
};

std::ostream& operator<<(std::ostream& izlaz, const KompleksanBroj& z);
std::istream& operator>>(std::istream& ulaz, KompleksanBroj& z);

#endif