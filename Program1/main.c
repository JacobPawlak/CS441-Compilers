/*** main.c  * from Aho, Sethi, Ullman**/

#include "global.h"
#include <stdio.h> /* added JWJ */
#include <time.h> /* added JWJ for time */

//Jacob Pawlak
//CS441G Compilers
//October 7th, 2017
//pa1

int main()
{
        lineno = 1; 
	init();
	//changed to my name and added the branch441 language
   	printf("recursive descent for BRANCH441 Language: Jacob Pawlak, CS441G Compilers, BRANCH441 Project 1\n");
    	time_t t;
    	time(&t); printf("%s\n",ctime(&t));
	parse();
	//print_symbol_table();
	exit(0);  /* successful termination */
}

