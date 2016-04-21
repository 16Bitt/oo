#ifndef UTILS_H
#define UTILS_H

#include "stdbool.h"

#define MKNEW(tp)	((tp*) malloc(sizeof(tp)))

#define INTSWITCH(val) { int tmpswitchval = (val); if(false){
#define INTCASE(val) }else if((val) == tmpswitchval){
#define INTSWITCHEND } }
#define INTDEFAULT } else {

#endif
