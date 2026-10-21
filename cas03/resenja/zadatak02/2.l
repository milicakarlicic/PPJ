%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    int brojac = 0;
%}

%%

"("                 { brojac++; }

")"                 { 
    brojac--; 
    if (brojac < 0) {
        fprintf(stderr, "Imamo zatvorenu zagradu koja nije otvorena!\n");
        exit(EXIT_FAILURE);
    }
}

.                   { ECHO; }

%%

int main(int argc, char **argv) {
    yylex();

    if (brojac == 0) {
        printf("Sve ok!\n");
    } else {
        fprintf(stderr, "Imamo otvorene zagrade koje nisu zatvorene!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
