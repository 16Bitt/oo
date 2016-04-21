#ifndef OO_TYPE_H
#define OO_TYPE_H

#include "stdlib.h"
#include "oo_c_types.h"
#include "oo_var.h"

#define UNDEFINED_TYPE	0

typedef struct{
	char* name;
	method_list* methods;
	var_list* traits;
} type_container;

extern list_t* types;

type_t type_lookup(char* name);
void type_call(type_t type, char* opname);
void add_type(char* name);
void add_method(type_t type, char* name, type_t return_type, arg_list* args);
void add_trait(type_t type,  char* name, type_t vartype);
char* type_name(type_t tp);

#endif
