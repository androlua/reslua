#include "json.h"
#include <stdio.h>

// struct ItemNode{
// 	char *key;
// 	struct Node *value;	
// 	struct ItemNode *next;
// };

// struct Node{
// 	enum {
// 		NT_NUMBER,
// 		NT_STRING,
// 		NT_GROUP	
// 	}type;
// 	union{
// 		float number;
// 		char *string;
// 		ItemNode *children;
// 	};
// };

void printChar(int count, char c){
	while(count > 0){
		count --;
		putchar(c);
	}
}

static char * booleanStrings[] = {
	"false",
	"true"
};

void printInLua(struct Node *node, int deep){
	if(deep == 0){
		printf("local retJSON = ");
	}
	switch(node->type){
		case NT_NUMBER:
			printf("%f", node->number);
			break;
		case NT_STRING:
			printf("\"%s\"", node->string);
			break;
		case NT_BOOLEAN:
			printf("%s", booleanStrings[node->boolean]);
			break;
		case NT_GROUP:{
				struct ItemNode *list;
				printf("{\n");
				list = node->children;
				while(list){
					printChar(deep+1, '\t');
					printf("[\"%s\"] = ", list->key);
					printInLua(list->value, deep+1);
					if(list->next){
						printf(",\n");
					}
					else{
						printf("\n");
					}
					list = list->next;
				}
				printChar(deep, '\t');
				printf("}");
			}
			break;
	}
	if(deep == 0){
		printf("\n");
		printf("return retJSON\n");
	}
}

struct Node * newStringNode(char *string){
	struct Node *node = malloc(sizeof(struct Node));
	if(node != 0){
		node->type = NT_STRING;
		node->string = string;
		return node;
	}
	else{
		fprintf(stderr, "memory alloc failed.\n");
		exit(1);
	}
}
struct Node * newNumberNode(float number){
	struct Node *node = malloc(sizeof(struct Node));
	if(node != 0){
		node->type = NT_NUMBER;
		node->number = number;
		return node;
	}
	else{
		fprintf(stderr, "memory alloc failed.\n");
		exit(1);
	}
}

struct Node * newBooleanNode(int boolean){
	struct Node *node = malloc(sizeof(struct Node));
	if(node != 0){
		node->type = NT_BOOLEAN;
		node->boolean = boolean;
		return node;
	}
	else{
		fprintf(stderr, "memory alloc failed.\n");
		exit(1);
	}
}

struct Node * newGroupNode(struct ItemNode *itemNode){
	struct Node *node = malloc(sizeof(struct Node));
	if(node != 0){
		node->type = NT_GROUP;
		node->children = itemNode;
		return node;
	}
	else{
		fprintf(stderr, "memory alloc failed.\n");
		exit(1);
	}
}

struct ItemNode * ItemNodeListPrepend(struct ItemNode *list, struct ItemNode *item){
	item->next = list;
	return item;
}

struct ItemNode * newItemNode(char *key, struct Node *value){
	struct ItemNode *item = malloc(sizeof(struct ItemNode));
	if(item != 0){
		item->key = key;
		item->value = value;
		item->next = 0;
		return item;
	}
	else{
		fprintf(stderr, "memory alloc failed.\n");
		exit(1);
	}
}

void freeItemNodeList(struct ItemNode *list){
	struct ItemNode *next = 0;
	while(list != 0){
		next = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = next;
	}
}

void freeNode(struct Node *node){
	switch(node->type){
		case NT_NUMBER:
			break;
		case NT_STRING:
			free(node->string);
			break;
		case NT_GROUP:
			freeItemNodeList(node->children);
			break;
	}
	free(node);
}