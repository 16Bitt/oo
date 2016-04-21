#ifndef OO_VAR_H
#define OO_VAR_H

#include "stdlib.h"
#include "list.h"
#include "oo_c_types.h"

typedef struct{
	char* name;
	type_t type;
} var_t;

#define varget(ls, ind) ((var_t*) get(ls, (ind)))
#define varadd(ls, var) (append(ls, (void*) (var)))

#endif
