#include "string.h"
#include "oo_method.h"

method_t* find_method(method_list* list, char* name){
	int length = len(list);
	for(int i = 0; i < length; i++)
		if(strcmp(methodget(list, i)->name, name) == 0)
			return methodget(list, i);

	return NULL;
}
