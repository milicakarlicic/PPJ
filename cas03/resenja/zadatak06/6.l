%option noyywrap

%{
    #include <string.h>
    
    int vrednost = 0;   
%}

hiljade     M+

stotine     C{1,3}|CD|DC{0,3}|CM

desetice    X{1,3}|XL|LX{0,3}|XC

jedinice    I{1,3}|IV|VI{0,3}|IX

%%

{hiljade}                   {
    // yyleng = strlen(yytext)
    vrednost += yyleng * 1000;
}

{stotine}                   {
    if (strcmp(yytext, "CM") == 0) {
        vrednost += 900;
    }
    else if (strcmp(yytext, "CD") == 0) {
        vrednost += 400;
    }
    else {
        if (yytext[0] == 'D') {
            vrednost += 500 + (yyleng - 1) * 100;
        }
        else {
            vrednost += (yyleng) * 100;
        }
    }
}

{desetice}                  {
    if (strcmp(yytext, "XC") == 0) {
        vrednost += 90;
    }
    else if (strcmp(yytext, "XL") == 0) {
        vrednost += 40;
    }
    else {
        if (yytext[0] == 'L') {
            vrednost += 50 + (yyleng - 1) * 10;
        }
        else {
            vrednost += (yyleng) * 10;
        }
    }
}

{jedinice}                  {
    if (strcmp(yytext, "IX") == 0) {
        vrednost += 9;
    }
    else if (strcmp(yytext, "IV") == 0) {
        vrednost += 4;
    }
    else {
        if (yytext[0] == 'V') {
            vrednost += 5 + (yyleng - 1);
        }
        else {
            vrednost += yyleng;
        }
    }
}

.|\n                        {
    printf("%d", vrednost);
    vrednost = 0;
    ECHO;
}

%%

int main() { 
    yylex();

    return 0;
}