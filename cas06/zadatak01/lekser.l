%option noyywrap

%{
    #include <iostream>

    using namespace std;

    #include <vector>
    #include "Polinom.hpp"

    #include "parser.tab.hpp"
%}

%%

"poly"                                  { return POLY; }

"print"                                 { return PRINT; } 

"deg"                                   { return DEG; }

"int"                                   { return INT; }

"=="                                    { return JEDNAKO; }

"!="                                    { return RAZLICITO; }

[a-zA-Z_][a-zA-Z_0-9]*                  { 
    yylval.s = new string(yytext);
    return ID; 
} 

-?[0-9]+([.][0-9]+)?                    { 
    yylval.d = atof(yytext);
    return BROJ; 
}

[;()<>=,+\-*\[\]']                      { return *yytext; }

[ \t\n]                                 { }

.                                       {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%