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
    preduvid = yylex();
    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);
    while(!stek.empty()) {
        int element = stek.top();
        stek.pop();

        switch (element) {
            case NIZ_NAREDBI:
                if (preduvid == broj_tip || preduvid == stampaj) {
                    std::cout << "NIZ_NAREDBI -> NAREDBA ; NIZ_NAREDBI'\n";
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI] Ocekujem broj_tip ili stampaj");
                }
                break;
            case NIZ_NAREDBI_P:
                if (preduvid == broj_tip || preduvid == stampaj) {
                    std::cout << "NIZ_NAREDBI' -> NIZ_NAREDBI\n";
                    stek.push(NIZ_NAREDBI);
                } else if (preduvid == eoi) {
                    std::cout << "NIZ_NAREDBI' -> eps\n";
                } else {
                    greska("[NIZ_NAREDBI'] Ocekujem broj_tip, stampaj ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == broj_tip) {
                    std::cout << "NAREDBA -> broj_tip id DODELA\n";
                    stek.push(DODELA);
                    stek.push(id);
                    stek.push(broj_tip);
                } else if (preduvid == stampaj) {
                    std::cout << "NAREDBA -> stampaj ( NIZ_ARG )\n";
                    stek.push(')');
                    stek.push(NIZ_ARG);
                    stek.push('(');
                    stek.push(stampaj);
                } else {
                    greska("[NAREDBA] Ocekujem broj_tip ili stampaj");
                }
                break;
            case DODELA:
                if (preduvid == ';') {
                    std::cout << "DODELA -> eps\n";
                } else if (preduvid == dodela) {
                    std::cout << "DODELA -> dodela E\n";
                    stek.push(E);
                    stek.push(dodela);
                } else {
                    greska("[DODELA] Ocekujem ; ili dodela");
                }
                break;
            case E:
                if (preduvid == '-' || preduvid == sqrt_token || preduvid == id || preduvid == broj) {
                    std::cout << "E -> T E'\n";
                    stek.push(E_P);
                    stek.push(T);
                } else {
                    greska("[E] Ocekujem -, sqrt_token, id ili broj");
                }
                break;
            case E_P:
                if (preduvid == '+') {
                    std::cout << "E' -> + T E'\n";
                    stek.push(E_P);
                    stek.push(T);
                    stek.push('+');
                } else if (preduvid == '-') {
                    std::cout << "E' -> - T E'\n";
                    stek.push(E_P);
                    stek.push(T);
                    stek.push('-');
                } else if (preduvid == ')' || preduvid == ';' || preduvid == ',') {
                    std::cout << "E' -> eps\n";
                } else {
                    greska("[E'] Ocekujem +, -, ), ; ili ,");
                }
                break;
            case T:
                if (preduvid == '-') {
                    std::cout << "T -> - T\n";
                    stek.push(T);
                    stek.push('-');
                } else if (preduvid == sqrt_token) {
                    std::cout << "T -> sqrt_token ( E )\n";
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                    stek.push(sqrt_token);
                } else if (preduvid == id) {
                    std::cout << "T -> id\n";
                    stek.push(id);
                } else if (preduvid == broj) {
                    std::cout << "T -> broj\n";
                    stek.push(broj);
                } else {
                    greska("[T] Ocekujem -, sqrt_token, id ili broj");
                }
                break;
            case NIZ_ARG:
                if (preduvid == '-' || preduvid == sqrt_token || preduvid == id || preduvid == broj) {
                    std::cout << "NIZ_ARG -> E NIZ_ARG'\n";
                    stek.push(NIZ_ARG_P);
                    stek.push(E);
                } else {
                    greska("[NIZ_ARG] Ocekujem -, sqrt_token, id ili broj");
                }
                break;
            case NIZ_ARG_P:
                if (preduvid == ',') {
                    std::cout << "NIZ_ARG' -> , E NIZ_ARG'\n";
                    stek.push(NIZ_ARG_P);   
                    stek.push(E);
                    stek.push(',');
                } else if (preduvid == ')') {
                    std::cout << "NIZ_ARG' -> eps\n";
                } else {
                    greska("[NIZ_ARG'] Ocekujem , ili )");  
                }
                break;
        
            default:
                if (element != preduvid) {
                    greska("[Nepoklapanje tokena na ulazu i steku!");
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
