%option noyywrap

%{
    #include <stdio.h>
%}

%%

"include"|"define"|"int"|"char"|"while"|"if"|"return"|"else"    {
        fprintf(yyout, "<span style = color:blue>%s</span>", yytext);
    }

[a-zA-Z_][a-zA-Z_0-9]*                                          {
        fprintf(yyout, "<b>%s</b>", yytext);
    }

0|[1-9][0-9]*                                                   {
        fprintf(yyout, "<span style = color:green>%s</span>", yytext);
    }   

'(.|\\n)'                                                       {
        fprintf(yyout, "<span style = color:purple>%s</span>", yytext);
    }

["]([^\\]\\["]|[^"])*["]                                        {
        fprintf(yyout, "<span style = color:red>%s</span>", yytext);
    }

%%

int main(int argc, char **argv) {
    // kljucne reci: plave
    // id: boldovani
    // celobrojne konst: zelene
    // karakteri: ljubicasti
    if (argc <= 1 || (yyin = fopen(argv[1], "r")) == NULL) {
        yyin = stdin;
    }

    if (argc <= 2 || (yyout = fopen(argv[2], "w")) == NULL) {
        yyout = stdout;
    }

    fprintf(yyout, "<html><pre>");

    yylex();

    fprintf(yyout, "</pre></html>");

    if (yyin != stdin) {
        fclose(yyin);
    } 

    if (yyout != stdin) {
        fclose(yyout);
    } 

    return 0;
}