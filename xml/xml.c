#include "xml.h"
#include <stdio.h>

// struct AttrNode{
// 	char *key;
// 	char *value;
// 	struct AttrNode *next;
// };

// struct Node{
// 	enum{
// 		NT_EMPTY,
// 		NT_TEXT,
// 		NT_GROUP
// 	}type;

// 	union{
// 		char *text;
// 		struct Node *childList;
// 	};

// 	struct AttrNode *attrList;

// 	struct Node *next;
// };

void printChar(int count, char c){
	while(count > 0){
		count --;
		putchar(c);
	}
}


void printInLua(struct Node *node, int deep){

	struct AttrNode *attrs;

	if(deep == 0){
		printf("local retXML = ");
	}

	printf("{\n");
	printChar(deep+1, '\t');
	printf("[\"name\"] = \"%s\",\n", node->name);

	switch(node->type){
		case NT_EMPTY:
			printChar(deep+1, '\t');
			printf("[\"type\"] = \"%s\",\n", "NT_EMPTY");
			break;
		case NT_TEXT:
			printChar(deep+1, '\t');
			printf("[\"type\"] = \"%s\",\n", "NT_TEXT");
			printChar(deep+1, '\t');
			printf("[\"text\"] = \"%s\",\n", node->text);
			break;
		case NT_GROUP:{
				struct Node *list = node->childList;
				int index;
				printChar(deep+1, '\t');
				printf("[\"type\"] = \"%s\",\n", "NT_GROUP");
				printChar(deep+1, '\t');
				printf("[\"children\"] = {\n");

				index = 1;
				while(list){
					printChar(deep+2, '\t');
					printf("[%d] = ", index);
					printInLua(list, deep+2);
					if(list->next)
						printf(",\n");
					else
						printf("\n");
					list = list->next;
					index ++;
				}
				printChar(deep+1, '\t');
				printf("},\n");
			}
			break;
	}
	printChar(deep+1, '\t');
	printf("[\"attrs\"] = {\n");

	attrs = node->attrList;
	while(attrs){
		printChar(deep+2, '\t');
		printf("[\"%s\"] = \"%s\"", attrs->key, attrs->value);
		if(attrs->next){
			printf(",");
		}
		printf("\n");
		attrs = attrs->next;
	}
	printChar(deep+1, '\t');
	printf("}\n");
	printChar(deep, '\t');
	printf("}");

	if(deep == 0){
		printf("\n\n");
		printf("return retXML\n");
	}
}

void freeAttrNodeList(struct AttrNode *list){
	struct AttrNode *next = 0;
	while(list){
		next = list->next;

		free(list->key);
		free(list->value);
		free(list);

		list = next;
	}
}

void freeChildList(struct Node *list){
	struct Node *next;
	while(list){
		next = list->next;
		freeNode(list);
		list = next;
	}
}

void freeNode(struct Node *node){
	switch(node->type){
		case NT_TEXT:
			free(node->text);
			break;
		case NT_EMPTY:
			break;
		case NT_GROUP:
			freeChildList(node->childList);
			break;
	}
	free(node->name);
	freeAttrNodeList(node->attrList);
	free(node);
}

struct Node * nodeSetText(struct Node *node, char *text){
	node->type = NT_TEXT;
	node->text = text;
}

struct Node * nodeSetGroup(struct Node *node, struct Node *childList){
	node->type = NT_GROUP;
	node->childList = childList;
}

struct Node * nodeListAppend(struct Node *nodeList, struct Node *node){
	if(nodeList == 0){
		return node;
	}
	else{
		struct Node *lastNode = nodeList;
		while(lastNode->next){
			lastNode = lastNode->next;
		}
		lastNode->next = node;
		return nodeList;
	}
}

struct Node * newNode(char *name, struct AttrNode *attrList){
	struct Node * node = malloc(sizeof(struct Node));
	if(node != 0){
		node->name = name;
		node->type = NT_EMPTY;
		node->attrList = attrList;
		node->next = 0;
		return node;
	}
	else{
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
}

struct AttrNode * attrListPrepend(struct AttrNode *attrList, struct AttrNode *attrNode){
	attrNode->next = attrList;
	return attrNode;
}

struct AttrNode * newAttrNode(char *key, char *value){
	struct AttrNode * attrNode = malloc(sizeof(struct AttrNode));
	if(attrNode != 0){
		attrNode -> key = key;
		attrNode -> value = value;
		attrNode -> next = 0;
		return attrNode;
	}
	else{
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
}
