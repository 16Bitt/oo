#include "stdlib.h"
#include "ctype.h"

#include "operator.h"
#include "expression.h"
#include "oo_scope.h"
#include "oo_type.h"
#include "oo_class.h"
#include "utils.h"
#include "libcc.h"

type_t curtype = UNDEFINED_TYPE;
type_t prevtype = UNDEFINED_TYPE;

void term(){
	//Lookup our base types
	type_t int_type		= type_lookup("IntegerValue");
	type_t string_type	= type_lookup("StringValue");
	type_t char_type 	= type_lookup("CharacterValue");

	//Our variable, if needed
	var_scope_t* var	= NULL;

	//Save the old type-- we're moving on
	prevtype = curtype;

	//If it's a plain old number, you know what to do
	if(isdigit(look))
		curtype = int_type;
	
	//It must be a string
	if(look == '"')
		curtype = string_type;

	//It must be a character
	if(look == '\'')
		curtype = char_type;

	//Case for parentheses-- solve the contained expression
	if(look == '('){
		type_t save = prevtype;		//Save our old type
		match("(");
		expression();
		match(")");
		prevtype = save;		//Restore it
	}
	
	if(isalpha(look)){
		char* found = getname();
		var = search_scope(found);
		if(var == NULL)
			error("Identifier %s not found in scope", found);
		curtype = var->tp;
	}

	//If there's a type mismatch, try to convert
	if((curtype != prevtype) && (prevtype != UNDEFINED_TYPE)){
		char* op = dynstring("to%s", type_name(curtype));
		type_call(prevtype, op);
		free(op);
	}
	
	//Start parsing...
	INTSWITCH(curtype)
		INTCASE(int_type)
			emitln("LOAD REGISTER0, %s", getnumber());

		INTCASE(string_type)
			char* str = getstring('"');
			emitln("LOAD REGISTER0, %s", add_string(str));
		
		INTCASE(char_type)
			match("'");
			emitln("LOAD REGISTER0, %d", (int) look);
			getcharacter();
			match("'");
		
		INTDEFAULT
			emitln("LOAD REGISTER0, ARG%d", var->arg_offset);

	INTSWITCHEND
}

void expression(){
	prevtype = UNDEFINED_TYPE;
	term();
	while(is_operator(look)){
		emitln("PUSH REGISTER0");
		operator();
	}
}
