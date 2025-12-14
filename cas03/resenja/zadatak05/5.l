%option noyywrap

%{
    #include <stdio.h>

    #define CELOBROJNA_KONST    1
    #define REALNA_KONST        2
%}

digit   [0-9]

%%

[+-]?{digit}+                               { 
    return CELOBROJNA_KONST;
}

[+-]?{digit}+[.]{digit}+(e[+-]{digit}+)?    {
    return REALNA_KONST;
}

.|\n                                        { }

%%

int main(int argc, char **argv) {
    // yyin i yyout - promenljive iz lex.yy.c koje predstavljaju ulaz odnosno izlaz za funkciju yylex odnosno pise
    // podrazumevano yyin = stdin i yyout = stdout

    if (argc >= 2) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            yyin = stdin;
        }
    }
    if (argc == 3) {
        yyout = fopen(argv[2], "w");
        if (yyout == NULL) {
            yyout = stdout;
        }
    }

    int token;
    while((token = yylex()) != 0) {
        if (token == CELOBROJNA_KONST) {
            // char *yytext  - promenljiva iz lex.yy.c u kojoj se cuva prepoznata leksema
            fprintf(yyout, "Celobrojna konstanta: %d\n", atoi(yytext)); 
        } else if (token == REALNA_KONST) {
            fprintf(yyout, "Realna konstanta: %.15lf\n", atof(yytext)); 
        }
    }

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}