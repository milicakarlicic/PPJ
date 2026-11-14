%option noyywrap

%{
    #include <iostream>
    #include "tokeni.hpp"
%}

%%

"broj"                      { return broj_tip; }

"stampaj"                   { return stampaj; }

"sqrt"                      { return sqrt_token; }

[a-zA-Z_][a-zA-Z_0-9]*      { return id; }

[0-9]+([.][0-9]+)?          { return broj; }

":="                        { return dodela; }

[;\-+(),]                   { return *yytext; }

[ \n\t]                     { }

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
