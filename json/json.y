%{

#include <stdio.h>
#include "json.h"

%}

%union{
	char *string;
	float number;
	int boolean;
	struct Node *node;
	struct ItemNode *itemNode;
};

%token <boolean> BOOLEAN;
%token <number> NUMBER
%token <string> STRING

%type <node> json json1 json2
%type <itemNode> list item


%%
json:	json1 {$$ = $1; printInLua($$, 0); freeNode($$);}
	|	json2 {$$ = $1; printInLua($$, 0); freeNode($$);}
	;

json1:	STRING	{$$ = newStringNode($1);}
	|	NUMBER	{$$ = newNumberNode($1);}
	|	BOOLEAN {$$ = newBooleanNode($1);}
	;

json2:	'{' '}'	{$$ = newGroupNode(0);}
	|	'{' list '}'	{$$ = newGroupNode($2);}
	;

list:	item	{$$ = $1;}
	|	item ',' list	{$$ = ItemNodeListPrepend($3, $1);}
	;

item:	STRING ':' json1	{$$ = newItemNode($1, $3);}
	|	STRING ':' json2	{$$ = newItemNode($1, $3);}
	;

%%

int main(){
	return yyparse();
}

void yyerror(char *s){
	fprintf(stderr, "error: %s\n", s);
}