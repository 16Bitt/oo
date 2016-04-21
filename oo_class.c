#include "stdlib.h"
#include "string.h"

#include "oo_type.h"
#include "arg_list.h"
#include "utils.h"
#include "libcc.h"
#include "oo_block.h"
#include "oo_class.h"
#include "oo_scope.h"
#include "oo_method.h"
#include "expression.h"

type_t current_class = UNDEFINED_TYPE;
type_t return_type = UNDEFINED_TYPE;

void fn_stmt(){
	match("fn");
	
	//Get the return type and validate it
	char* typename = getname();
	type_t type = type_lookup(typename);
	if(type == UNDEFINED_TYPE)
		error("Unknown return type in function definition");
	
	//Get the function name
	char* fnname = getname();
	
	//Get the argument list
	list_t* args = mklist();
	
	//Add 'this' to args
	arg_t* arg = MKNEW(arg_t);
	arg->name = "this";
	arg->type = current_class;
	append(args, arg);
	
	//Add each argument
	match("(");
	while(look != ')'){
		arg_t* arg = MKNEW(arg_t);
		type_t tp = type_lookup(getname());
		if(tp == UNDEFINED_TYPE)
			error("Unknown argument type in function definition");
		
		arg->type = tp;
		arg->name = getname();
		append(args, arg);
		
		if(look != ')')
			match(",");
	}
	match(")");
	
	//Set the return type for block()
	return_type = type;
	
	/*char* fname = dynstring("%s__%s", type_name(current_class), fnname);
	putlabel(fname);
	free(fname);
	*/
		
	emitln_notab("%s__%s:", type_name(current_class), fnname);

	//Add a method and label and compile the function
	add_method(current_class, fnname, type, args);

	start_scope();
	int length = len(args);
	for(int i = length - 1; i >= 0; i--){
		arg_t* arg = argget(args, i);
		add_to_scope(arg->name, arg->type);
	}
	block();
	end_scope();

	return_type = UNDEFINED_TYPE;
}

void var_stmt(){
	match("var");
	char* typename = getname();
	type_t type = type_lookup(typename);
	if(type == UNDEFINED_TYPE)
		error("Invalid type in variable declaration");
	
	char* name = getname();

	if(current_class != UNDEFINED_TYPE){
		match(";");
		add_trait(current_class, name, type);
	}

	//Handle local variables
	else{
		add_to_scope(name, type);

		if(look != '='){
			match(";");
			return;
		}

		match("=");
		expression();
		match(";");
		//TODO: assignment
	}
}

void class_stmt(){
	match("class");
	
	//Get and add the new type name
	char* type = getname();
	add_type(type);
	current_class = type_lookup(type);
	
	match("{");
	while(look != '}'){
		char* op = peekname();
		STRSWITCH(op)
			STRCASE("fn")
				fn_stmt();
			STRCASE("var")
				var_stmt();
			STRDEFAULT
				error("Not a function or variable declaration");
		STRSWITCHEND
	}
	match("}");
	
	//Reset our current class type
	current_class = UNDEFINED_TYPE;
}

void class_trait(){
	char* name = getname();
	var_scope_t* var = search_scope(name);

	if(var == NULL)
		error("Identifier '%s' undefined", name);

	curtype = var->tp;
	emitln("LOAD REGISTER0, ARG%d", var->arg_offset);

	if(look == '.'){
		match(".");
		char* attr = getname();
		if(is_trait(curtype, attr)){
			get_trait(curtype, attr);
		} else if(is_method(curtype, attr)){
					
		} else {
			error("'%s' has no attribute '%s'", name, attr);
		}
	}
}

bool is_trait(type_t type, char* name){
	type_container* tc = (type_container*) get(types, type);
	size_t length = len(tc->traits);
	for(size_t i = 0; i < length; i++){
		var_t* var = varget(tc->traits, i);
		if(strcmp(var->name, name) == 0)
			return true;
	}

	return false;
}

bool is_method(type_t type, char* name){
	type_container* tc = (type_container*) get(types, type);
	size_t length = len(tc->methods);
	for(size_t i = 0; i < length; i++){
		method_t* mt = methodget(tc->traits, i);
		if(strcmp(mt->name, name) == 0)
			return true;
	}

	return false;
}

void get_trait(type_t type, char* name){
	prevtype = curtype;
	if(!is_trait(type, name))
		error("no trait named '%s'", name);

	type_container* tc = (type_container*) get(types, type);
	size_t length = len(tc->traits);
	for(size_t i = 0; i < length; i++){
		var_t* var = varget(tc->traits, i);
		if(strcmp(var->name, name) == 0){
			curtype = var->type;
			emitln("UADD REGISTER0, TRAIT%d", i);
			emitln("LOADV REGISTER1, REGISTER0");
			emitln("LOAD REGISTER0, REGISTER1");
			return;
		}
	}

	error("Fatal trait error for '%s'", name);
}
