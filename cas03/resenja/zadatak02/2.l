%option noyywrap

%{
    // ovaj blok koda se unosi pri pocetku datoteke lex.yy.c
    // sluzi za ukljucivanje zaglavlja i definisanje globalnih promenljivih

    #include <stdio.h>

    int brojac_redova = 0;
    int brojac_karaktera = 0;

%}

    // regularne definicije i direktive

%%
    // sekcija za regularne izraze i njima odgovarajuce akcije

\n              { brojac_redova++; brojac_karaktera++; }

.               { brojac_karaktera++; }

%%

// ova sekcija koda se unosi na sam kraj datoteke lex.yy.c

int main() {
    yylex();
    
    printf("Brojac redova: %d\n", brojac_redova);
    printf("Brojac karaktera: %d\n", brojac_karaktera);

    return 0;
}