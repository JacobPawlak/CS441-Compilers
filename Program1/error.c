/***********  error.c **from Aho, Sethi, Ullman***********/

//Jacob Pawlak
//CS441G Compilers
//October 7th, 2017
//pa1

#include "global.h"

void error(m)    /*generate all error messagese */
	char *m;
{
	fprintf(stderr, "line %d; %s\n", lineno, m);
	exit(1);  /* unsuccessful termination  */
}

