%option noyywrap

%{
    #include <iostream>
    #include <map>
    #include <set>
    #include "Graf.hpp"
    #include "parser.tab.hpp"

%}

%%

"begin"                     { return BEGIN_T; }

"graph"                     { return GRAPH_T; }

"print_matrix_d"            { return PRINT_D_T; }

"print_matrix_u"            { return PRINT_U_T; }

"end"                       { return END_T; }

"delete"                    { return DELETE_T; }

[a-zA-Z_][a-zA-Z_0-9]*      { 
    yylval.id = new std::string(yytext);
    return ID_T; 
}

0|[1-9][0-9]*               { 
    yylval.i = atoi(yytext);
    return BROJ_T; 
}

[(){}\[\];:,=+*~]           { return *yytext; }

[ \t\n]|"//".*              {}

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%