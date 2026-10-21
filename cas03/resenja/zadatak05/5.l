%option noyywrap

%{
    #include <stdio.h>

    #define CELOBROJNA_KONST    (1)
    #define REALNA_KONST        (2)
%}

cifra   [0-9]

%%

[+-]?{cifra}+                               { return CELOBROJNA_KONST; }

[+-]?{cifra}+[.]{cifra}+(e[+-]{cifra}+)?    { return REALNA_KONST; }

.|\n                                        { }

%%

int main(int argc, char **argv) {
    int token;
    while((token = yylex()) != 0) {
        if (token == CELOBROJNA_KONST) {
            // char *yytext - promenljiva iz lex.yy.c u kojoj se cuva prepoznata leksema
            fprintf(yyout, "Celobrojna konstanta: %d\n", atoi(yytext)); 
        } else if (token == REALNA_KONST) {
            fprintf(yyout, "Realna konstanta: %.15lf\n", atof(yytext)); 
        }
    }

    return 0;
}
