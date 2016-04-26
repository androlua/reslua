%{

#include <stdio.h>
#include "xml.h"

%}

%union{
	char *string;
	struct AttrNode *attrNode;
	struct Node *node;	
};



%token <string> NAME TEXT STRING

%type <attrNode> attr attrList
%type <node> open openClose nodeList node


%%
XML:	node {printInLua($1, 0); freeNode($1);}

node:	openClose { $$ = $1; }
	|	open TEXT close { $$ = nodeSetText($1, $2); }
	|	open nodeList close { $$ = nodeSetGroup($1, $2); }
	;

nodeList: { $$ = 0; }
	|	nodeList node { $$ = nodeListAppend($1, $2); }
	;

openClose:	'<'	NAME attrList '/' '>' { $$ = newNode($2, $3); }
	;

close:	'<' '/' NAME '>' {}
	;

open:	'<' NAME attrList '>' { $$ = newNode($2, $3); }
	;

attrList:	 {$$ = 0;}
	|	attr attrList { $$ = attrListPrepend($2, $1); }
	;

attr:	NAME '=' STRING {$$ = newAttrNode($1, $3); }
	;

%%

int main(){
	return yyparse();
}

void yyerror(char *s){
	fprintf(stderr, "error: %s\n", s);
}