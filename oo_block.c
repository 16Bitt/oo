#include "stdlib.h"
#include "string.h"

#include "oo_type.h"
#include "libcc.h"
#include "oo_block.h"
#include "oo_class.h"
#include "expression.h"

void line(){
	char* op = peekname();
	STRSWITCH(op)
		STRCASE("var")
			var_stmt();
		STRDEFAULT
			class_trait();
			if(look == '='){
				match("=");
				expression();
				emitln("POP REGISTER1");
				emitln("STORE REGISTER1, REGISTER0");
			}
			match(";");
	STRSWITCHEND
}

void assignment(){
	match("=");
	emitln("PUSH REGISTER0");
	type_t loadtype = curtype;
	line();
	if(curtype != loadtype){
		//FIXME
		char* op = dynstring("%d__to%d", curtype, loadtype);
		type_call(curtype, "op");
		free(op);
	}
	emitln("PUSH REGISTER0");
	//FIXME
	type_call(loadtype, "=");
}

void block(){
	match("{");
	while(look != '}'){
		char* peek = peekname();
		STRSWITCH(peek)
			STRCASE("if");
				if_stmt();
			STRCASE("while");
				while_stmt();
			STRCASE("each");
				each_stmt();
			STRDEFAULT
				line();
		STRSWITCHEND
	}
	match("}");
}

void if_stmt(){
	match("if");
	match("(");
	expression();
	match(")");

	char* lbl_false = getlabel();
	emitln("GOTOZ %s", lbl_false);		//False: goto the label
	block();
	
	if(strcmp(peekname(), "else") == 0){	//Edge case: else
		match("else");
		
		char* lbl_end = getlabel();
		emitln("GOTO %s", lbl_end);	//Case done, leave
		putlabel(lbl_false);		//False, continue execution
		block();
		putlabel(lbl_end);		//End label
		
		free(lbl_end);
	}

	else
		putlabel(lbl_false);
	
	free(lbl_false);
}

void while_stmt(){
	char* lbl_top = getlabel();
	char* lbl_bot = getlabel();
	
	putlabel(lbl_top);	//Label is placed before evaluation
	match("while");
	match("(");
	expression();		//Check the condition each time
	match(")");
	emitln("GOTOZ %s", lbl_bot);
	block();
	emitln("GOTO %s", lbl_top);
	putlabel(lbl_bot);

	free(lbl_top);		//Clean up our labels
	free(lbl_bot);
}

//TODO
void each_stmt(){

}
