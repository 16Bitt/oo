#ifndef OO_METHOD_H
#define OO_METHOD_H

#include "stdlib.h"
#include "list.h"
#include "oo_c_types.h"

typedef struct{
	char* name;
	type_t return_type;
	arg_list* arguments;
	char* label_start;
} method_t;

#define methodget(ls, ind) ((method_t*) get(ls, ind))
#define methodadd(ls, mt) (append(ls, (void*) (mt)))

method_t* find_method(method_list* list, char* name);

#endif
