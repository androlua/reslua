%option noyywrap

%x IN
%x COMMENT
%x INSTRING

%{

	#include "xml.tab.h"
	#include <string.h>

%}

%%

\<!\-\- {BEGIN COMMENT;}
<COMMENT>\-\-\> {BEGIN INITIAL;}
<COMMENT>. {}
<COMMENT>\n {}


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

<IN>\" {BEGIN INSTRING;}
<INSTRING>\" {BEGIN IN;}
<INSTRING>[^\"]+ {yylval.string = strdup(yytext); return STRING;};



[ \t\n\r]+ {}

[^\<\>\n\r\t ]+	{yylval.string = strdup(yytext); return TEXT;}

%%