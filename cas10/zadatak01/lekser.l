%option noyywrap

%{
    #include <iostream>
    #include "SintaksnoStablo.hpp"
    #include "parser.tab.hpp"

%}

%%

"begin"                     { return BEGIN_T; } // koristimo sufiks _T jer je makro BEGIN definisan u parser.tab.hpp fajlu...

"end"                       { return END_T; }

"while"                     { return WHILE_T; }

"then"                      { return THEN_T; }

"if"                        { return IF_T; }

"print"                     { return PRINT_T; }

"else"                      { return ELSE_T; }

"do"                        { return DO_T; }

[a-zA-Z_][a-zA-Z_0-9]*      { 
    yylval.s = new std::string(yytext);
    return ID_T; 
}

[<>()+\-.;]                 { return *yytext; }

":="                        { return DODELA_T; }

"=="                        { return JEDNAKO_T; }

0|[1-9][0-9]*               { 
    yylval.i = atoi(yytext);
    return BROJ_T; 
}

[ \t\n]                     { }

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%