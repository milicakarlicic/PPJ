%option noyywrap

%{
    #include <stdio.h>
%}

%%

"{"[^}]*"}"                            { }

"(*"([^*]|"*"[^)])*"*"*"*)"            { }

%%

int main() {
    yylex();

    return 0;
}