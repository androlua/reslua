%option noyywrap

%x IN

%{

	#include "xml.tab.h"
	#include <string.h>

%}

%%

<IN>[ \t] {}
<IN>\n {}
<IN>\r {}
<IN>\/	{return yytext[0];}

<IN>!	{return yytext[0];}
<IN>\?	{return yytext[0];}
<IN>=	{return yytext[0];}
\<	{BEGIN IN; return yytext[0];}
\<\?.*\> {}
\<!.*\> {}
<IN>\>	{BEGIN INITIAL; return yytext[0];}

<IN>[^\"!\+\-\{\}\[\]\\,\.\?\<\>\t\n\r\=\/ ]+	{yylval.string = strdup(yytext); return NAME;}

<IN>\"[^\"]*\"	{yytext[strlen(yytext)-1]=0; yylval.string = strdup(yytext+1); return STRING;}

[ \t\n\r]+ {}

[^\<\>\n\r\t ]+	{yylval.string = strdup(yytext); return TEXT;}

%%