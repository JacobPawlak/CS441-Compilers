/****  init.c  ***from Aho, Sethi, Ullman*********/
/*
Jacob Pawlak
CS441G Compliers
October 7th, 2017
pa1

*/

#include "global.h"

struct entry keywords[] = {
  {"div", DIV},
  {"mod", MOD},
  {0, 0}
};
void init()   /* loads keywords into symtable  */
{
	struct entry *p;
	for (p= keywords; p-> token; p++)
		lookup(p->lexptr, p->token); /* lookup now inserts if missing */
}


