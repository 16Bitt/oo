#ifndef LIST_H
#define LIST_H

#include "stdlib.h"

typedef struct node{
	void* value;
	struct node* next;
} node_t;

typedef struct list{
	size_t len;
	node_t* head;
} list_t;

list_t* mklist();
void rmlist(list_t* list);
size_t len(list_t* list);
void* first(list_t* list);
void* last(list_t* list);
void* get(list_t* list, size_t index);
void linsert(list_t* list, size_t index, void* value);
void lremove(list_t* list, size_t index);
void printlist(list_t* list);
void append(list_t* list, void* value);
void* pop(list_t* list);

#endif
