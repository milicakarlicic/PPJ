#include <iostream>
#include <stack>
#include "tokeni.hpp"

// Gramatika:                       Skupovi izbora:     

// E -> T E'                        {(, broj}        
// E' -> + T E'                     {+}
//      | eps                       {), eoi}    
// T -> F T'                        {(, broj}    
// T' -> * F T'                     {*}
//      | eps                       {+, ), eoi}
// F -> ( E )                       {(}
//      | broj                      {broj}

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

extern int yylex();

int main() {
    int preduvid = yylex();

    std::stack<int> stek; 
    stek.push(E);
    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();

        switch (element) {
            case E:
                if (preduvid == '(' || preduvid == broj) {
                    std::cout << "E => T E'\n";
                    stek.push(EP);
                    stek.push(T);
                } else {
                    greska("[E] Ocekujem ( ili broj");
                }
                break;
            case EP:
                if (preduvid == '+') {
                    std::cout << "E' => + T E'\n";
                    stek.push(EP);
                    stek.push(T);
                    stek.push('+');
                } else if (preduvid == ')' || preduvid == eoi) {
                    std::cout << "E' => eps\n";
                } else {
                    greska("[E'] Ocekujem +, ( ili eoi");
                }
                break;
            case T:
                if (preduvid == '(' || preduvid == broj) {
                    std::cout << "T => F T'\n";
                    stek.push(TP);
                    stek.push(F);
                } else {
                    greska("[T] Ocekujem ( ili broj");
                }
                break;
            case TP:
                if (preduvid == '*') {
                    std::cout << "T' => * F T'\n";
                    stek.push(TP);
                    stek.push(F);
                    stek.push('*');
                } else if (preduvid == '+' || preduvid == ')' || preduvid == eoi) {
                    std::cout << "T' => eps\n";
                } else {
                    greska("[T'] Ocekujem +, ( ili eoi");
                }
                break;
            case F:
                if (preduvid == '(') {
                    std::cout << "F => ( E )\n";
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                } else if (preduvid == broj) {
                    std::cout << "F => broj\n";
                    stek.push(broj);
                } else {
                    greska("[F] Ocekujem ( ili broj");
                }
                break;
            default:
                // slucaj kada se na vrhu steka nalazi token
                if (preduvid != element) {
                    greska("Nepoklapanje tokena sa ulaza i na vrhu steka!");
                }
                preduvid = yylex();
        }
    }

    if (preduvid == eoi) {
        std::cout << "Prihvaceno!\n";
    } else {
        std::cout << "Nije prihvaceno!\n";
    }
}