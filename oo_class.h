#ifndef OO_STATE_H
#define OO_STATE_H

#include "stdlib.h"
#include "stdbool.h"
#include "oo_type.h"

extern type_t current_class;
extern type_t return_type;

void class_stmt();
void fn_stmt();
void var_stmt();

bool is_trait(type_t type, char* name);
bool is_method(type_t type, char* name);
void get_trait(type_t type, char* name);
void class_trait();

#endif
