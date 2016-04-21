//Standard headers
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

//OO headers
#include "oo_type.h"
#include "operator.h"
#include "expression.h"

//Libcc headers
#include "libcc.h"

bool is_operator(char c){
	char* str = dynstring("%c", look);
	bool ret = is_in(str, "+", "-", "*", "/", ">", "<", "&", "|", "^", "%", NULL);
	free(str);
	return ret;
}

char* match_operator(){
	if(!is_operator(look))
		expected("operator method");

	char* op = dynstring("%c", look);
	match(op);
	if(is_operator(look)){
		match(op);
		char* old = op;
		op = dynstring("%s%s", old, old);
		free(old);
	}

	return op;
}

void operator(){
	char* opname = match_operator();
	term();
	emitln("PUSH REGISTER0");
	type_call(curtype, opname);
}
