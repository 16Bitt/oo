#ifndef ARG_LIST_H
#define ARG_LIST_H

#include "list.h"
#include "stdbool.h"
#include "oo_c_types.h"

typedef struct arg{
	type_t type;
	char* name;
} arg_t;

#define argfirst(ls) ((arg_t*) first(ls))
#define arglast(ls) ((arg_t*) last(ls))
#define argget(ls, ind) ((arg_t*) get(ls, (ind)))

#endif
