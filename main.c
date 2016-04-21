#include "stdio.h"
#include "libcc.h"
#include "list.h"
#include "oo_block.h"
#include "oo_class.h"
#include "oo_program.h"

int main(int argc, char** argv){
	libcc_init(stdin, stdout, stderr);
	
	add_type("UNDEFINED_TYPE");
	add_type("None");
	add_type("IntegerValue");
	add_type("CharacterValue");
	add_type("StringValue");
	
	program();
	emit_strings("%s: db \"%s\", 0");

	return 0;
}
