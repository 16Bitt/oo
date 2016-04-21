#ifndef LIBCC_STATE_H
#define LIBCC_STATE_H

#include "stdlib.h"
#include "stdio.h"
#include "list.h"
#include "libcc.h"

//How many states we can hold nested
#define STATE_STACK_SIZE	16

//This struct backs up the state of our libcc instance
typedef struct{
	unsigned char look;
	size_t line_no;
	char* filename;
	FILE* code_input;
} libcc_state_t;

void libcc_backup();
void libcc_restore();

#endif
