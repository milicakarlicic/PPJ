%option noyywrap

%{
    #include <iostream>
    #include "tokeni.hpp"
%}

%%

"list<number>"                      { return list_num; }

"list<string>"                      { return list_str; }

".print()"                          { return print; }

".print_r()"                        { return print_r; }

0|[1-9][0-9]*                       { return broj;}

[a-zA-Z_][a-zA-Z0-9_]*              { return id; }

[{};,=]                             { return *yytext; }

["][^"]*["]                         { return str; }

[ \t\n]+                            { }

.                                   {
        std::cerr << "Leksicka greska: " << yytext << std::endl;
        exit(EXIT_FAILURE);
    }

%%

int main () {
    while (yylex() != 0) {
        std::cout << "Token: " << yytext << std::endl;
    }
}