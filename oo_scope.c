#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "oo_type.h"
#include "list.h"
#include "utils.h"
#include "oo_scope.h"
#include "libcc.h"

list_t* scope_list = NULL;

void start_scope(){
	if(scope_list == NULL)
		scope_list = mklist();
	
	//Make a new variable, flagged as a new scope with no type and no name
	var_scope_t* sc = MKNEW(var_scope_t);
	sc->ident	= "";
	sc->tp		= UNDEFINED_TYPE;
	sc->scope_start	= true;
	
	//Add it to the list
	append(scope_list, sc);
}

void end_scope(){
	if(scope_list == NULL)
		scope_list = mklist();
	
	//Pop elements off the stack and free them
	//When we find a scope_start flag, we know we're done
	size_t length = len(scope_list);
	if(length != 0)
		for(int i = length - 1; i >= 0; i--){
			var_scope_t* sc = (var_scope_t*) pop(scope_list);
			bool flag = sc->scope_start;
			free(sc);
			if(flag)
				return;
		}
	
	//For some reason no scope_start was found in the entire list, bail out
	error("Scope ended before a scope was opened");
}

void add_to_scope(char* ident, type_t tp){
	if(scope_list == NULL)
		scope_list = mklist();

	var_scope_t* sc = MKNEW(var_scope_t);
	sc->ident	= ident;
	sc->tp		= tp;
	sc->scope_start	= false;

	//Find our previous scope to know the new offset
	size_t length = len(scope_list);
	if(length != 0)
		for(int i = length - 1; i >= 0; i--){
			var_scope_t* v = scopeget(scope_list, i);
			if(v->scope_start == true)
				sc->arg_offset = v->arg_offset++;
		}
	
	append(scope_list, sc);
}

var_scope_t* search_scope(char* ident){
	if(scope_list == NULL)
		scope_list = mklist();
	
	//Search backwards to respect our scoping rules
	size_t length = len(scope_list);
	if(length == 0)
		return NULL;

	for(size_t i = length - 1; i >= 0; i--){
		var_scope_t* sc = scopeget(scope_list, i);
		if(strcmp(sc->ident, ident) == 0)
			return sc;
		if(sc->scope_start == true)
			return NULL;
	}
	
	//Something is very wrong...
	error("No scope in scope search");

	//This won't be reached...
	return NULL;
}
