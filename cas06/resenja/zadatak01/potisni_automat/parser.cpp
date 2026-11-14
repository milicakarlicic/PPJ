#include <iostream>
#include <stack>
#include "tokeni.hpp"

extern int yylex();

int preduvid;

void greska(std::string poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    std::stack<int> stek;

    preduvid = yylex();
    stek.push(NIZ_NAREDBI);

    while (!stek.empty()) {
        int simbol = stek.top();
        stek.pop();

        switch (simbol) {
            case NIZ_NAREDBI:
                if (preduvid == id || preduvid == print) {
                    std::cout << "NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI_P" << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI] Ocekujem id ili print");
                }
                break;

            case NIZ_NAREDBI_P:
                if (preduvid == id || preduvid == print) {
                    std::cout << "NIZ_NAREDBI' => NAREDBA ; NIZ_NAREDBI'" << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else if (preduvid == eoi) {
                    std::cout << "NIZ_NAREDBI' => eps" << std::endl;
                } else {
                    greska("[NIZ_NAREDBI'] Ocekujem id, print ili eoi");
                }
                break;

            case NAREDBA:
                if (preduvid == id) {
                    std::cout << "NAREDBA => id = E" << std::endl;
                    stek.push(E);
                    stek.push('=');
                    stek.push(id);
                } else if (preduvid == print) {
                    std::cout << "NAREDBA => print ( E )" << std::endl;
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                    stek.push(print);
                } else {
                    greska("[NAREDBA] Ocekujem id ili print");
                }
                break;

            case E:
                if (preduvid == id || preduvid == '(' || preduvid == '-' || preduvid == broj) {
                    std::cout << "E => T E'" << std::endl;
                    stek.push(E_P);
                    stek.push(T);
                } else {
                    greska("[E] Ocekujem id, (, - ili broj");
                }
                break;

            case E_P:
                if (preduvid == '+') {
                    std::cout << "E' => + T E'" << std::endl;
                    stek.push(E_P);
                    stek.push(T);
                    stek.push('+');
                } else if (preduvid == '-') {
                    std::cout << "E' => - T E'" << std::endl;
                    stek.push(E_P);
                    stek.push(T);
                    stek.push('-');
                } else if (preduvid == ')' || preduvid == ';') {
                    std::cout << "E' => eps" << std::endl;
                } else {
                    greska("[E_P] Ocekujem +, -, ) ili ;");
                }
                break;

            case T:
                if (preduvid == id || preduvid == '(' || preduvid == '-' || preduvid == broj) {
                    std::cout << "T => F T'" << std::endl;
                    stek.push(T_P);
                    stek.push(F);
                } else {
                    greska("[T] Ocekujem id, (, - ili broj");
                }
                break;

            case T_P:
                if (preduvid == '*') {
                    std::cout << "T' => * F T'" << std::endl;
                    stek.push(T_P);
                    stek.push(F);
                    stek.push('*');
                } else if (preduvid == '/') {
                    std::cout << "T' => / F T'" << std::endl;
                    stek.push(T_P);
                    stek.push(F);
                    stek.push('/');
                } else if (preduvid == ')' || preduvid == ';' || preduvid == '+' || preduvid == '-') {
                    std::cout << "T' => eps" << std::endl;
                } else {
                    greska("[T'] Ocekujem *, /, ), ;, + ili -");
                }
                break;

            case F:
                if (preduvid == broj) {
                    std::cout << "F => broj" << std::endl;
                    stek.push(broj);
                } else if (preduvid == '(') {
                    std::cout << "F => ( E )" << std::endl;
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                } else if (preduvid == id) {
                    std::cout << "F => id" << std::endl;
                    stek.push(id);
                } else if (preduvid == '-') {
                    std::cout << "F => - F" << std::endl;
                    stek.push(F);
                    stek.push('-');
                } else {
                    greska("[F] Ocekujem broj, (, id ili -");
                }
                break;

            default:
                if (simbol != preduvid) {
                    greska("Nepoklapanje tokena na steku i ulazu!");
                }
                preduvid = yylex();
        }
    }

    if (preduvid == eoi) {
        std::cout << "Sve ok\n";
    } else {
        std::cout << "Nije ok\n";
    }

    return 0;
}
