#include "stdlib.h"
#include "string.h"

#include "list.h"
#include "oo_type.h"
#include "utils.h"
#include "libcc.h"
#include "oo_method.h"

//This will get initialized in main(), most likely
list_t* types = NULL;

//Get a type index so we don't have to do a strcmp over a list every time
type_t type_lookup(char* name){
	//If we haven't added the type for whatever reason, then no type
	if(types == NULL)
		return UNDEFINED_TYPE;
	
	//Do a simple string comparison to find the type name in the types list
	size_t length = len(types);
	for(size_t i = 0; i < length; i++){
		type_container* t = (type_container*) get(types, i);
		if(strcmp(t->name, name) == 0)
			return (type_t) i;
	}
	
	//No type was found with that name, return nothing
	return UNDEFINED_TYPE;
}

void type_call(type_t type, char* opname){
	emitln("ROUTINE %s__%s", type_name(type), opname);
}

void add_type(char* name){
	if(types == NULL)
		types = mklist();
	
	if(type_lookup(name) != UNDEFINED_TYPE)
		error("Redefinition of type '%s'", name);

	type_container* t = MKNEW(type_container);
	t->name		= name;
	t->methods	= mklist();
	t->traits	= mklist();

	append(types, (void*) t);
}

void add_method(type_t type, char* name, type_t return_type, arg_list* args){
	type_container* tp = (type_container*) get(types, type);
	if(tp == NULL)
		error("No type to add method '%s' to", name);
	
	//Fill the container
	method_t* method = MKNEW(method_t);
	method->name		= name;
	method->return_type	= return_type;
	method->arguments	= args;
	method->label_start	= getlabel();
	
	//Add it to the type list
	append(tp->methods, method);
	
	//Throw down a label
	putlabel(method->label_start);
}

char* type_name(type_t tp){
	if(types == NULL)
		error("No known types for lookup of type_t=%d", tp);
	
	if(tp >= len(types))
		error("Unknown type for type_t=%d", tp);

	type_container* t = get(types, tp);

	return t->name;
}

void add_trait(type_t type, char* name, type_t vartype){
	type_container* tp = (type_container*) get(types, type);
	if(tp == NULL)
		error("Can't add trait to invalid type");

	//Create and initialize the new variable object
	var_t* var = MKNEW(var_t);
	var->name = name;
	var->type = vartype;

	//Add it to the list
	append(tp->traits, var);
}
