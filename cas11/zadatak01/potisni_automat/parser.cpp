#include <iostream>
#include <stack>
#include "tokeni.hpp"

// Gramatika sa skupovima izbora:

// program: naredba ';' program_p      {ID, PRINT_T}
// program_p: naredba ';' program_p    {ID, PRINT_T}
//       | eps                         {EOI}
// naredba: ID = e                     {ID}
//       | PRINT ( e )                 {PRINT_T}
// e -> t e_p                          {(, BROJ, ID, -}
// e_p -> + t e_p                      {+}
//       | - t e_p                     {-}
//       | eps                         {;, )}
// t -> f t_p                          {(, BROJ, ID, -}
// t_p -> * f t_p                      {*}
//       | / f t_p                     {/}
//       | eps                         {+, -, ;, )}
// f -> ( e )                          {(}
//       | BROJ                        {broj}
//       | ID                          {ID}
//       | - f                         {-}

int yylex();

int preduvid;

void greska(const std::string& poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    std::stack<int> stek;

    preduvid = yylex();
    stek.push(program);

    while (!stek.empty()) {
        int simbol = stek.top();
        stek.pop();

        switch (simbol) {
            case program:
                if (preduvid == ID || preduvid == PRINT) {
                    std::cout << "program => naredba ; program'" << std::endl;
                    stek.push(program_p);
                    stek.push(';');
                    stek.push(naredba);
                } else {
                    greska("[program] Ocekujem ID ili PRINT");
                }
                break;

            case program_p:
                if (preduvid == ID || preduvid == PRINT) {
                    std::cout << "program' => naredba ; program'" << std::endl;
                    stek.push(program_p);
                    stek.push(';');
                    stek.push(naredba);
                } else if (preduvid == EOI) {
                    std::cout << "program' => Eps" << std::endl;
                } else {
                    greska("[program_p] Ocekujem ID, PRINT ili EOI");
                }
                break;

            case naredba:
                if (preduvid == ID) {
                    std::cout << "naredba => ID = e" << std::endl;
                    stek.push(e);
                    stek.push('=');
                    stek.push(ID);
                } else if (preduvid == PRINT) {
                    std::cout << "naredba => print ( e )" << std::endl;
                    stek.push(')');
                    stek.push(e);
                    stek.push('(');
                    stek.push(PRINT);
                } else {
                    greska("[naredba] Ocekujem ID, PRINT ili EOI");
                }
                break;

            case e:
                if (preduvid == ID || preduvid == '(' || preduvid == '-' || preduvid == BROJ) {
                    std::cout << "e => t e'" << std::endl;
                    stek.push(e_p);
                    stek.push(t);
                } else {
                    greska("[e] Ocekujem ID, (, - ili BROJ");
                }
                break;

            case e_p:
                if (preduvid == '+') {
                    std::cout << "e' => + t e'" << std::endl;
                    stek.push(e_p);
                    stek.push(t);
                    stek.push('+');
                } else if (preduvid == '-') {
                    std::cout << "e' => - t e'" << std::endl;
                    stek.push(e_p);
                    stek.push(t);
                    stek.push('-');
                } else if (preduvid == ')' || preduvid == ';') {
                    std::cout << "e' => Eps" << std::endl;
                } else {
                    greska("[e_p] Ocekujem +, -, ) ili ;");
                }
                break;

            case t:
                if (preduvid == ID || preduvid == '(' || preduvid == '-' || preduvid == BROJ) {
                    std::cout << "t => f t'" << std::endl;
                    stek.push(t_p);
                    stek.push(f);
                } else {
                    greska("[t] Ocekujem ID, (, - ili BROJ");
                }
                break;

            case t_p:
                if (preduvid == '*') {
                    std::cout << "t' => * f t'" << std::endl;
                    stek.push(t_p);
                    stek.push(f);
                    stek.push('*');
                } else if (preduvid == '/') {
                    std::cout << "t' => / f t'" << std::endl;
                    stek.push(t_p);
                    stek.push(f);
                    stek.push('/');
                } else if (preduvid == ')' || preduvid == ';' || preduvid == '+' || preduvid == '-') {
                    std::cout << "t' => Eps" << std::endl;
                } else {
                    greska("[t_p] Ocekujem *, /, ), ;, + ili -");
                }
                break;

            case f:
                if (preduvid == BROJ) {
                    std::cout << "f => BROJ" << std::endl;
                    stek.push(BROJ);
                } else if (preduvid == '(') {
                    std::cout << "f => ( e )" << std::endl;
                    stek.push(')');
                    stek.push(e);
                    stek.push('(');
                } else if (preduvid == ID) {
                    std::cout << "f => ID" << std::endl;
                    stek.push(ID);
                } else if (preduvid == '-') {
                    std::cout << "f => - f" << std::endl;
                    stek.push(f);
                    stek.push('-');
                } else {
                    greska("[f] Ocekujem BROJ, (, ID ili -");
                }
                break;

            default:
                if (simbol != preduvid) {
                    greska("Nepoklapanje tokena na steku i ulazu!");
                }
                preduvid = yylex();
        }
    }

    std::cout << "sve ok" << std::endl;

    return 0;
}
