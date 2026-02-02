%option noyywrap

%{
    #include <iostream>

    #include "tokeni.hpp"
%}

%%

"print"                     { return PRINT; }

[a-zA-Z_][a-zA-Z_0-9]*      { return ID; }

0|[1-9][0-9]*               { return BROJ; }

[;()\-+/*=]                 { return *yytext; }

[ \n\t]                     { }

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
