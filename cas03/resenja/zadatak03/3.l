%option noyywrap

%{
    #include <stdio.h>
%}

%%

"{"[^}]*"}"                          { } 

"(*"([^\n*]|[*][^)])*[*]*"*)"        { }        

%%

int main(int argc, char **argv) {
    yylex();

    return 0;
}
