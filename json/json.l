%option noyywrap

%{

	#include "json.tab.h"

%}

%%

\"[^\"]*\" {yytext[strlen(yytext)-1]=0; yylval.string = strdup(yytext+1); return STRING;}
(\+|\-)?[0-9]+(\.[0-9]+)? {yylval.number = atof(yytext); return NUMBER;}

, |
: |
\{ |
\} {return yytext[0];}

\n {}
[ \t] {}
. {printf("error niu2x\n");}

%%