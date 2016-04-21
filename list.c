#include "stdlib.h"

//OO Specific
#include "list.h"
#include "utils.h"
#include "oo_error.h"

//For debugging
#include "libcc.h"

list_t* mklist(){
	list_t* list = MKNEW(list_t);
	list->len	= 0;
	list->head	= NULL;
	return list;
}

node_t* getnode(list_t* list, size_t index){
	node_t* current = list->head;
	for(int i = 0; i < index; i++){
		if(current == NULL){
			printlist(list);
			err("Index out of bounds in getnode()");
		}
		current = current->next;
	}

	return current;
}

node_t* mknode(void* value, node_t* next){
	node_t* n = MKNEW(node_t);
	n->value = value;
	n->next = next;

	return n;
}

void rmlist(list_t* list){
	int i;
	for(i = list->len - 1; i >= 0; i--)
		free(getnode(list, i));
}

size_t len(list_t* list){
	return list->len;
}

node_t* head(list_t* list){
	return list->head;
}

node_t* tail(list_t* list){
	return getnode(list, len(list) - 1);
}

void* first(list_t* list){
	return head(list)->value;
}

void* last(list_t* list){
	return tail(list)->value;
}

void* get(list_t* list, size_t index){
	return getnode(list,index)->value;
}

void append(list_t* list, void* value){
	if(len(list) != 0)
		tail(list)->next = mknode(value, NULL);
	else
		list->head = mknode(value, NULL);
	list->len++;
}

void linsert(list_t* list, size_t index, void* value){
	node_t* n = getnode(list, index);
	n->next = mknode(value, n->next);
	list->len++;
}

void lremove(list_t* list, size_t index){
	if(index == 0){
		node_t* n = head(list);
		list->head = head(list)->next;
		free(n);
		list->len--;
		return;
	}

	node_t* n = getnode(list, index - 1);
	node_t* rem = n->next;
	n->next = rem->next;
	free(rem);
	list->len--;
}

void* pop(list_t* list){
	if(len(list) == 0)
		error("Popping from empty list");
	void* val = last(list);
	lremove(list, list->len - 1);
	return val;
}

void printlist(list_t* list){
	size_t length = len(list);
	node_t* current = list->head;

	size_t i = 0;
	while(current != NULL){
		printf("%lX[%ld]\t= %lX\n", (size_t) list, (size_t) i, (size_t) current->value);
		current = current->next;
		i++;
	}
	if(i != length)
		warning("Size mismatch in list: %d != %d", i, length);
}
