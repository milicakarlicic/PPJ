%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    void ispisi(char *tekst);
%}

%%

#(.|\\\n)*                                                  { 
    fprintf(yyout, "<span style=\"color:green\">");
    ispisi(yytext);
    fprintf(yyout, "</span>");
}

"/*"([^*]|[*][^/])*"*/"                                     { fprintf(yyout, "<span style=\"color:grey\">%s</span>", yytext); }

"if"|"while"|"return"|"else"|"int"|"char"                   { fprintf(yyout, "<B><span style=\"color:blue\">%s</span></B>", yytext); }

[a-zA-Z_][a-zA-Z_0-9]*                                      { fprintf(yyout, "<B>%s</B>", yytext); }

["]([^"]|[^\]\\["])*["]                                     { fprintf(yyout, "<span style=\"color:red\">%s</span>", yytext); }

%%

void ispisi(char *tekst) {
    for (int i = 0; i < strlen(tekst); i++) {
        if (tekst[i] == '<') {
            fprintf(yyout, "&lt");
        } else if (tekst[i] == '>') {
            fprintf(yyout, "&gt");
        } else if (tekst[i] == '&') {
            fprintf(yyout, "&amp");
        } else {
            fprintf(yyout, "%c", tekst[i]);
        }
    }
}

int main(int argc, char **argv) {
    // preprocesorske direktive zelene
    // komentari sivi
    // kljucne reci boldovane i plave
    // stringovi crveni
    // identifikatori boldovani

    if (argc == 1 || (yyin = fopen(argv[1], "r")) == NULL) {
        yyin = stdin;
    }

    if (argc == 2 || (yyout = fopen(argv[2], "w")) == NULL) {
        yyout = stdout;
    }

    fprintf(yyout, "<html><body><pre>");
    yylex();
    fprintf(yyout, "</pre></body></html>");

    if (yyin != stdin) {
        fclose(yyin);
    }

    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}