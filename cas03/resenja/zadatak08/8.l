%option noyywrap

%{
    #include <stdio.h>

    #define EOI                 (0)
    #define KLJUCNA_REC         (256)
    #define ID                  (257)
    #define OP                  (258)
    #define SEP                 (259)
    #define LITERAL             (260)
%}

%%

"var"|"begin"|"if"|"then"|"end"|"integer"   { return KLJUCNA_REC; }

[a-zA-Z_][a-zA-Z_0-9]*                      { return ID; }

[,:;.()]                                    { return SEP; }

[+>]|:=                                     { return OP; }

0|[1-9][0-9]*                               { return LITERAL; }

[ \n\t]                                     { }

%%

int main() {
    int token;
    while ((token = yylex()) != EOI) {
        switch (token) {
            case ID:
                fprintf(yyout, "ID: %s\n", yytext);
                break;
            case KLJUCNA_REC:
                fprintf(yyout, "KLJUCNA_REC: %s\n", yytext);
                break;
            case SEP:
                fprintf(yyout, "SEP: %s\n", yytext);
                break;
            case OP:
                fprintf(yyout, "OP: %s\n", yytext);
                break;
            case LITERAL:
                fprintf(yyout, "LITERAL: %d\n", atoi(yytext));
                break;
            default:
                fprintf(stderr, "Nepostojeci token!");
                break;
        }
    }

    return 0;
}
