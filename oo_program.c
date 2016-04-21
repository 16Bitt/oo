#include "stdlib.h"
#include "string.h"
#include "oo_program.h"
#include "oo_class.h"
#include "libcc.h"

void program(){
	char* name = peekname();
	while(!libcc_eof){
		STRSWITCH(name)
			STRCASE("class")
				class_stmt();
			STRDEFAULT
				error("Unknown operation %s", name);
		STRSWITCHEND
		
		name = peekname();
	}
}
