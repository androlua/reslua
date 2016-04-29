json: json.y json.l json.c json.h
	bison -d json.y
	flex json.l
	gcc -o json json.c json.tab.c lex.yy.c
all: json