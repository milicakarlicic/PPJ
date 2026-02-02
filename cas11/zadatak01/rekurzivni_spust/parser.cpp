#include <iostream>
#include "tokeni.hpp"

/ Gramatika sa skupovima izbora:

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

void program(void);
void program_p(void);
void naredba(void);
void e(void);
void e_p(void);
void t(void);
void t_p(void);
void f(void);

int main() {
    preduvid = yylex();
    program();
    if (preduvid == EOI) {
        std::cout << "sve ok" << std::endl;
    } else {
        std::cout << "nije ok" << std::endl;
    }

    return 0;
}

void program(void) {
    if (preduvid == ID || preduvid == PRINT) {
        std::cout << "program => naredba ; program'" << std::endl;
        naredba();

        if (preduvid != ';') {
            greska("[program] Ocekujem ;");
        }
        preduvid = yylex();
        
        program_p();
    } else {
        greska("[program] Ocekujem ID ili PRINT");
    }
}

void program_p(void) {
    if (preduvid == ID || preduvid == PRINT) {
        std::cout << "program' => naredba ; program'" << std::endl;
        naredba();

        if (preduvid != ';') {
            greska("[program_p] Ocekujem ;");
        }
        preduvid = yylex();
        
        program_p();
    } else if (preduvid == EOI) {
        std::cout << "program' => Eps" << std::endl;
    } else {
        greska("[program_p] Ocekujem ID, PRINT ili EOI");
    }
}

void naredba(void) {
    if (preduvid == ID) {
        std::cout << "naredba => ID = e" << std::endl;
        preduvid = yylex();
        if (preduvid != '=') {
            greska("Ocekujem =");
        }
        preduvid = yylex();
        e();
    } else if (preduvid == PRINT) {
        std::cout << "naredba => PRINT ( e )" << std::endl;
        preduvid = yylex();

        if (preduvid != '(') {
            greska("[naredba] Ocekujem (");
        }
        preduvid = yylex();

        e();

        if (preduvid != ')') {
            greska("[naredba] Ocekujem )");
        }
        preduvid = yylex();
    } else {
        greska("[naredba] Ocekujem ID ili PRINT");
    }
}

void e(void) {
    if (preduvid == '(' || preduvid == BROJ || preduvid == ID || preduvid == '-') {
        std::cout << "e => t e'" << std::endl;
        t();
        e_p();
    } else {
        greska("[e] Ocekujem (, BROJ, ID ili -");
    }
}

void e_p(void) {
    if (preduvid == '+') {
        std::cout << "e' => + t e'" << std::endl;
        preduvid = yylex();
        t();
        e_p();
    } else if (preduvid == '-') {
        std::cout << "e' => - t e'" << std::endl;
        preduvid = yylex();
        t();
        e_p();
    } else if (preduvid == ')' || preduvid == ';') {
        std::cout << "e' => Eps" << std::endl;
    } else {
        greska("[e_p] Ocekujem +, -, ) ili ;");
    }
}

void t(void) {
    if (preduvid == '(' || preduvid == BROJ || preduvid == ID || preduvid == '-') {
        std::cout << "t => f t'" << std::endl;
        f();
        t_p();
    } else {
        greska("[t] Ocekujem (, BROJ, ID ili -");
    }
}

void t_p(void) {
    if (preduvid == '*') {
        std::cout << "t' => * f t'" << std::endl;
        preduvid = yylex();
        f();
        t_p();
    } else if (preduvid == '/') {
        std::cout << "t' => / f t'" << std::endl;
        preduvid = yylex();
        f();
        t_p();
    } else if (preduvid == '+' || preduvid == '-' || preduvid == ')' || preduvid == ';') {
        std::cout << "t' => Eps" << std::endl;
    } else {
        greska("[t_p] Ocekujem *, /, +, -, ) ili ;");
    }
}

void f(void) {
    if (preduvid == '(') {
        std::cout << "f => ( e )" << std::endl;
        preduvid = yylex();
        e();

        if (preduvid != ')') {
            greska("[f] Ocekujem )");
        }
        preduvid = yylex();
    } else if (preduvid == BROJ) {
        std::cout << "f => BROJ" << std::endl;
        preduvid = yylex();
    } else if (preduvid == ID) {
        std::cout << "f => ID" << std::endl;
        preduvid = yylex();
    } else if (preduvid == '-') {
        std::cout << "f => - f" << std::endl;
        preduvid = yylex();
        f();
    } else {
        greska("[f] Ocekujem (, BROJ, ID ili -");
    }
}