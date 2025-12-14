%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    #define KLJUCNA_REC     1
    #define ID              2
    #define OP              3
    #define INTERPUNKCIJA   4
    #define KONSTANTA       5
    #define ZAGRADA         6
%}

D        [0-9]

%%

"var"|"if"|"integer"|"begin"|"end"|"then"           { return KLJUCNA_REC; }

[a-zA-Z_][a-zA-Z_{D}]*                              { return ID; }

">"|"+"|":="                                        { return OP; }

[;,.:]                                              { return INTERPUNKCIJA; }

{D}+                                                { return KONSTANTA; }

[()]                                                { return ZAGRADA; }

[ \n\t]                                             { }

.                                                   { 
    fprintf(stderr, "Leksicka greska: %s", yytext);
    exit(EXIT_FAILURE);
}

%%

int main(int argc, char **argv) {
    if (argc == 1 || (yyin = fopen(argv[1], "r")) == NULL) {
            yyin = stdin;
    }

    int token;
    while ((token = yylex()) != 0) {
        switch (token) {
            case KLJUCNA_REC:
                fprintf(yyout, "KLJUCNA REC: %s\n", yytext);
                break;
            case ID:
                fprintf(yyout, "ID: %s\n", yytext);
                break;
            case OP:
                fprintf(yyout, "OP: %s\n", yytext);
                break;
            case INTERPUNKCIJA:
                fprintf(yyout, "INTERPUNKCIJA: %s\n", yytext);
                break;
            case KONSTANTA:
                fprintf(yyout, "KONSTANTA: %s\n", yytext);
                break;
            case ZAGRADA:
                fprintf(yyout, "ZAGRADA: %s\n", yytext);
                break;
        }
    }

    if (yyin != stdin) {
        fclose(yyin);
    }

    return 0;
}