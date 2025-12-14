%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"print"                     { return PRINT; }

"=="                        { return JEDNAKO; }

"!="                        { return RAZLICITO; }

[0-9]+                      {
    yylval.i = atoi(yytext);
    return BROJ; 
}

[a-zA-Z_][a-zA-Z_0-9]*      { 
    yylval.s = new string(yytext);
    return ID; 
}  

[+*;\-/=()]                 { return *yytext; } 

[ \n\t]|"//".*              { }

.                           {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);   
}

%%