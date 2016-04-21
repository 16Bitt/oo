#ifndef OO_SCOPE_H
#define OO_SCOPE_H

#include "stdbool.h"
#include "oo_type.h"
#include "stdlib.h"
#include "list.h"

typedef struct{
	char* ident;
	type_t tp;
	bool scope_start;
	int arg_offset;
} var_scope_t;

void start_scope();
void end_scope();
void add_to_scope(char* ident, type_t tp);
var_scope_t* search_scope(char* ident);

//Wrap list_t to use with var_scope_t*'s
#define scopefirst(ls) ((var_scope_t*) first(ls))
#define scopelast(ls) ((var_scope_t*) last(ls))
#define scopeget(ls, ind) ((var_scope_t*) get(ls, (ind)))

#endif
