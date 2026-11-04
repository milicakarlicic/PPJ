#include <iostream>
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

void E();
void EP();
void T();
void TP();
void F();

int preduvid;

extern int yylex();

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    preduvid = yylex();
    E();
    if (preduvid != eoi) {
        greska("Recenica se ne prihvata!");
    } else {
        std::cout << "Recenica prihvacena! :)\n";
    }

    return 0;
}

void E() {
    if (preduvid == '(' || preduvid == broj) {
        std::cout << "E => T E'\n";
        T();
        EP();
    } else {
        greska("[E] Ocekujem ( ili broj!");
    }
}

void EP() {
    if (preduvid == '+') {
        std::cout << "E' => + T E'\n";
        preduvid = yylex();
        T();
        EP();
    } else if (preduvid == ')' || preduvid == eoi) {
        std::cout << "E' => eps\n";
    } else {
        greska("[E'] Ocekujem +, ) ili eoi!");
    }
}

void T() {
    if (preduvid == '(' || preduvid == broj) {
        std::cout << "T => F T'\n";
        F();
        TP();
    } else {
        greska("[T] Ocekujem ( ili broj!");
    }
}

void TP() {
    if (preduvid == '*') {
        std::cout << "T' => * F T'\n";
        preduvid = yylex();
        F();
        TP();
    } else if (preduvid == '+' || preduvid == ')' || preduvid == eoi) {
        std::cout << "T' => eps\n";
    } else {
        greska("[T'] Ocekujem +, ), * ili eoi!");
    }
}

void F() {
    if (preduvid == '(') {
        std::cout << "F => ( E )\n";
        preduvid = yylex();
        E();
        // ako token nije na pocetku pravila neophodna provera poklapanja
        if (preduvid != ')') {
            greska("[F] Ocekujem )!");
        }
        preduvid = yylex();
    } else if (preduvid == broj) {
        std::cout << "F => broj\n";
        preduvid = yylex();
    } else {
        greska("[F] Ocekujem ) ili eoi!");
    }
}