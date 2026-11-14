#include <iostream>
#include "tokeni.hpp"

extern int yylex();

int preduvid;

void greska(std::string poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

void NIZ_NAREDBI();
void NIZ_NAREDBI_P();
void NAREDBA();
void E();
void E_P();
void T();
void T_P();
void F();

int main() {
    preduvid = yylex();
    NIZ_NAREDBI();
    if (preduvid == eoi) {
        std::cout << "Sve ok\n";
    } else {
        std::cout << "Nije ok\n";
    }

    return 0;
}

void NIZ_NAREDBI() {
    if (preduvid == id || preduvid == print) {
        std::cout << "NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI" << std::endl;
        NAREDBA();

        if (preduvid != ';') {
            greska("[NIZ_NAREDBI] Ocekujem ;");
        }
        preduvid = yylex();
        
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI] Ocekujem id ili print");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == id || preduvid == print) {
        std::cout << "NIZ_NAREDBI_P => NAREDBA ; NIZ_NAREDBI_P" << std::endl;
        NAREDBA();

        if (preduvid != ';') {
            greska("[NIZ_NAREDBI'] Ocekujem ;");
        }
        preduvid = yylex();
        
        NIZ_NAREDBI_P();
    } else if (preduvid == eoi) {
        std::cout << "NIZ_NAREDBI_P => eps" << std::endl;
    } else {
        greska("[NIZ_NAREDBI_P] Ocekujem id, print ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == id) {
        std::cout << "NAREDBA => id = E" << std::endl;
        preduvid = yylex();
        if (preduvid != '=') {
            greska("Ocekujem =");
        }
        preduvid = yylex();
        E();
    } else if (preduvid == print) {
        std::cout << "NAREDBA => print ( E )" << std::endl;
        preduvid = yylex();

        if (preduvid != '(') {
            greska("[NAREDBA] Ocekujem (");
        }
        preduvid = yylex();

        E();

        if (preduvid != ')') {
            greska("[NAREDBA] Ocekujem )");
        }
        preduvid = yylex();
    } else {
        greska("[NAREDBA] Ocekujem id ili print");
    }
}

void E() {
    if (preduvid == '(' || preduvid == broj || preduvid == id || preduvid == '-') {
        std::cout << "E => T E'" << std::endl;
        T();
        E_P();
    } else {
        greska("[E] Ocekujem (, broj, id ili -");
    }
}

void E_P() {
    if (preduvid == '+') {
        std::cout << "E' => + T E'" << std::endl;
        preduvid = yylex();
        T();
        E_P();
    } else if (preduvid == '-') {
        std::cout << "E' => - T E'" << std::endl;
        preduvid = yylex();
        T();
        E_P();
    } else if (preduvid == ')' || preduvid == ';') {
        std::cout << "E' => eps" << std::endl;
    } else {
        greska("[E_P] Ocekujem +, -, ) ili ;");
    }
}

void T() {
    if (preduvid == '(' || preduvid == broj || preduvid == id || preduvid == '-') {
        std::cout << "T => F T'" << std::endl;
        F();
        T_P();
    } else {
        greska("[T] Ocekujem (, broj, id ili -");
    }
}

void T_P() {
    if (preduvid == '*') {
        std::cout << "T' => * F T'" << std::endl;
        preduvid = yylex();
        F();
        T_P();
    } else if (preduvid == '/') {
        std::cout << "T' => / F T'" << std::endl;
        preduvid = yylex();
        F();
        T_P();
    } else if (preduvid == '+' || preduvid == '-' || preduvid == ')' || preduvid == ';') {
        std::cout << "T' => eps" << std::endl;
    } else {
        greska("[T_P] Ocekujem *, /, +, -, ) ili ;");
    }
}

void F() {
    if (preduvid == '(') {
        std::cout << "F => ( E )" << std::endl;
        preduvid = yylex();
        E();

        if (preduvid != ')') {
            greska("[F] Ocekujem )");
        }
        preduvid = yylex();
    } else if (preduvid == broj) {
        std::cout << "F => broj" << std::endl;
        preduvid = yylex();
    } else if (preduvid == id) {
        std::cout << "F => id" << std::endl;
        preduvid = yylex();
    } else if (preduvid == '-') {
        std::cout << "F => - F" << std::endl;
        preduvid = yylex();
        F();
    } else {
        greska("[F] Ocekujem (, broj, id ili -");
    }
}