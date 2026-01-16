%option noyywrap
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include "SintaksnoStablo.hpp"

    #include "parser.tab.hpp"
%}

%%

"def"                   { return DEF; } 

"print"                 { return PRINT; }

"=="                    { return JEDNAKO; }

[a-zA-Z_][a-zA-Z_0-9]*  { 
    yylval.s = new std::string(yytext); // string*
    return ID; 
}

[0-9]+([.][0-9]+)?      { 
    yylval.d = atof(yytext); // double
    return BROJ; 
}

[;(=)+\-*]              { return *yytext; }

[ \n\t]|"//".*          { }

.                       {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
