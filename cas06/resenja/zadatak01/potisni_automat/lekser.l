%option noyywrap

%{
    #include <iostream>
    #include "tokeni.hpp"
%}

%%

"print"                     { return print; }

[a-zA-Z_][a-zA-Z_0-9]*      { return id; }

0|[1-9][0-9]*               { return broj; }

[;()\-+/*=]                 { return *yytext; }

[ \n\t]                     { }

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
