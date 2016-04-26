#ifndef ___xml___
#define ___xml___

struct AttrNode{
	char *key;
	char *value;
	struct AttrNode *next;
};

struct Node{
	enum{
		NT_EMPTY,
		NT_TEXT,
		NT_GROUP
	}type;

	union{
		char *text;
		struct Node *childList;
	};
	char *name;
	struct AttrNode *attrList;

	struct Node *next;
};


void printInLua(struct Node *, int); 
void freeNode(struct Node *);
struct Node * nodeSetText(struct Node *, char *);
struct Node * nodeSetGroup(struct Node * , struct Node * );
struct Node * nodeListAppend(struct Node * , struct Node * );
struct Node * newNode(char *, struct AttrNode *);
struct AttrNode * attrListPrepend(struct AttrNode *, struct AttrNode *);
struct AttrNode * newAttrNode(char *, char *);


#endif