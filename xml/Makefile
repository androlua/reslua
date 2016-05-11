xml: xml.y xml.l xml.c xml.h
	bison -d xml.y
	flex xml.l
	gcc -o xml xml.c xml.tab.c lex.yy.c
all: xml