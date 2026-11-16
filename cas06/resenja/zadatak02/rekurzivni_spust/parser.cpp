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
void DODELA();
void E();
void E_P();
void T();
void T_P();
void NIZ_ARG();
void NIZ_ARG_P();

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
    if (preduvid == broj_tip || preduvid == stampaj) {
        std::cout << "NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI'\n";
        NAREDBA();
        if (preduvid != ';') {
            greska("[NIZ_NAREDBI] Ocekujem ;");
        }
        preduvid = yylex();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI] Ocekujem broj_tip ili stampaj");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == broj_tip || preduvid == stampaj) {
        std::cout << "NIZ_NAREDBI' => NIZ_NAREDBI\n";
        NIZ_NAREDBI();
    } else if (preduvid == eoi) {
        std::cout << "NIZ_NAREDBI' => eps\n";
    } else {
        greska("[NIZ_NAREDBI'] Ocekujem broj_tip, stampaj ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == broj_tip) {
        std::cout << "NAREDBA => broj_tip id DODELA\n";
        preduvid = yylex();
        if (preduvid != id) {
            greska("[NAREDBA] Ocekujem id");
        }
        preduvid = yylex();
        DODELA();
    } else if (preduvid == stampaj) {
        std::cout << "NAREDBA => stampaj ( NIZ_ARG )\n";
        preduvid = yylex();
        if (preduvid != '(') {
            greska("[NAREDBA] Ocekujem (");
        }
        preduvid = yylex();
        NIZ_ARG();
        if (preduvid != ')') {
            greska("[NAREDBA] Ocekujem )");
        }
        preduvid = yylex();
    } else {
        greska("[NAREDBA] Ocekujem broj_tip ili stampaj");
    }       
}

void DODELA() {
    if (preduvid == ';') {
        std::cout << "DODELA => eps\n";
    } else if (preduvid == dodela) {
        std::cout << "DODELA => dodela E \n";
        preduvid = yylex();
        E();
    } else {
        greska("[DODELA] Ocekujem ; ili dodela");
    }
}

void E() {
    if (preduvid == '-' || preduvid == sqrt_token || preduvid == id || preduvid == broj) {
        std::cout << "E => T E'\n";
        T();
        E_P();
    } else {
        greska("[E] Ocekujem -, sqrt_token, id ili broj");
    }
}

void E_P() {
    if (preduvid == '+') {
        std::cout << "E' => + T E'\n";
        preduvid = yylex();
        T();
        E_P();
    } else if (preduvid == '-') {
        std::cout << "E' => - T E'\n";
        preduvid = yylex();
        T();
        E_P();
    } else if (preduvid == ';' || preduvid == ')' || preduvid == ',') {
        std::cout << "E' => eps\n";
    } else {
        std::cout << "PREDUVID: " << char(preduvid) << std::endl;
        greska("[E'] Ocekujem +, -, ; ili )");
    }
}

void T() {
    if (preduvid == '-') {
        std::cout << "T => - T\n";
        preduvid = yylex();
        T();
    } else if (preduvid == sqrt_token) {
        std::cout << "T => sqrt_token ( E T_P\n";
        preduvid = yylex();
        if (preduvid != '(') {
            greska("[T] Ocekujem (");
        }
        preduvid = yylex();
        E();
        T_P();
    } else if (preduvid == id) {
        std::cout << "T => id\n";
        preduvid = yylex();
    } else if (preduvid == broj) {
        std::cout << "T => broj\n";
        preduvid = yylex();
    } else {
        greska("[T] Ocekujem -, sqrt_token, id ili broj");
    }
}

void T_P() {
    if (preduvid == ')') {
        std::cout << "T' => )\n";
        preduvid = yylex();
    } else if (preduvid == ',') {
        std::cout << "T' => , broj )\n";
        preduvid = yylex();
        if (preduvid != broj) {
            greska("[T'] Ocekujem broj");
        }
        preduvid = yylex();
        if (preduvid != ')') {
            greska("[T'] Ocekujem )");
        }
        preduvid = yylex();
    } else {
        greska("[T'] Ocekujem ) ili ,");
    }
}

void NIZ_ARG() {
    if (preduvid == '-' || preduvid == sqrt_token || preduvid == id || preduvid == broj) {
        std::cout << "NIZ_ARG => E NIZ_ARG'\n";
        E();
        NIZ_ARG_P();
    } else {
        greska("[NIZ_ARG] Ocekujem -, sqrt_token, id ili broj");
    }
}

void NIZ_ARG_P() {
    if (preduvid == ',') {
        std::cout << "NIZ_ARG' => , NIZ_ARG\n";
        preduvid = yylex();
        NIZ_ARG();
    } else if (preduvid == ')') {
        std::cout << "NIZ_ARG' => eps\n";
    } else {
        greska("[NIZ_ARG'] Ocekujem , ili )");
    }
}