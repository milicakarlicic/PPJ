%option noyywrap

%{
    #include <stdio.h>

    int brojac_linija = 0;
%}

%x komentar

%%

\n                  { ECHO; brojac_linija++; }

"/*"                { BEGIN(komentar); }

<komentar>[^*\n]    { }

<komentar>\n        { brojac_linija++; }

<komentar>[*]       { }

<komentar>"*/"      { BEGIN(INITIAL); }

%%

int main() {
    yylex();

    printf("\n\nBroj redova: %d\n", brojac_linija);

    return 0;
}