%option noyywrap

%{
    #include <iostream>
    #include "Funkcije.hpp"
    #include "parser.tab.hpp"

%}

%%

"sin"                   { return SIN; }

[x=+*()\[\]\n']         { return *yytext; }

[a-zA-Z_][a-zA-Z_0-9]*  { 
    yylval.s = new std::string(yytext);
    return ID; 
}

-?[0-9]+([.][0-9]+)?    { 
    yylval.d = atof(yytext);
    return BROJ; 
}

[ \t]|"//".*            { } 

.                       {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%