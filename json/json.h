#ifndef __json___
#define __json___

struct Node;

struct ItemNode{
	char *key;
	struct Node *value;	
	struct ItemNode *next;
};

struct Node{
	enum {
		NT_NUMBER,
		NT_STRING,
		NT_GROUP,
		NT_BOOLEAN
	}type;
	union{
		int boolean;
		float number;
		char *string;
		struct ItemNode *children;
	};
};


void printInLua(struct Node *, int);

struct Node * newStringNode(char *);
struct Node * newNumberNode(float );
struct Node * newBooleanNode(int);
struct Node * newGroupNode(struct ItemNode *);

struct ItemNode * ItemNodeListPrepend(struct ItemNode *, struct ItemNode *);

struct ItemNode * newStringItemNode(char *, char *);
struct ItemNode * newNumberItemNode(char *, float);
struct ItemNode * newGroupItemNode(char *, struct Node *);

void freeNode(struct Node *);

#endif