#include "stdlib.h"
#include "stdio.h"
#include "list.h"
#include "libcc.h"
#include "libcc_state.h"

libcc_state_t stack[STATE_STACK_SIZE];
size_t backup_index = 0;

//This saves the current state before we change files
//THIS DOES NOT COPY THE CURRENT STATE, IT SIMPLY HOLDS IT
void libcc_backup(){
	if(backup_index + 1 >= STATE_STACK_SIZE)
		error("state overflow");

	libcc_state_t* hold = &stack[backup_index++];
	hold->look		= look;
	hold->line_no		= line_no;
	hold->filename 		= NULL;		//FIXME
	hold->code_input	= code_input;
}

//Reverse the above
void libcc_restore(){
	libcc_state_t* hold = &stack[--backup_index];
	look		= hold->look;
	line_no		= hold->line_no;
	code_input	= hold->code_input;
	//FIXME-- Filename
}
