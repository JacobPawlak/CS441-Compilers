/*** parser.c  *****from Aho, Sethi, Ullman**************/

//Jacob Pawlak
//CS441G Compilers
//October 7th, 2017

#include "global.h"

int lookahead;
int error_count = 0;

void parse()   /*parses and VALIDATES BRANCH PROGRAMS NOW  */
{
	lookahead = yylex(); /* was lookahead = laxan() */
	while(lookahead != DONE) {
		//expr(); match(';');
		//begin to parse the program you are looking at
		parse_program();

	}

	if(error_count > 0){
		printf("Program Failed Parsing with %d errors\n", error_count);
	}
	else{
		printf("Program Passed Parsing\n");
	}

}

//Not really sure what to do with this here... so i guess i just leave it in?

/*
E -> TE'
 parse_E(){
   parse_term();
   Parse_E'();
}


E'-> +TE' | epsilon
 parse_E'() {
   if (lookahead == '+') {
       match('+');
       parse_T();
       parse_E'();
      }
   else
    if (lookahead == '+') {
       match('+');
       parse_T();
       parse_E'();
     }
   else error("unexpected token");
 }

The resulting code is a result of:
  -  removing the tail recursion from parse_E'()
  -  inlining the modified parse_E'() in parse_E().

*/

void expr()
{
	int t;
	term();
	while(1)
		switch (lookahead) {
		case '+': case '-':
			t=lookahead;
			match(lookahead); term(); emit(t, NONE);
			continue;
		default:
			return;
	}
}

/*
 T  -> FT'
 T' -> *FT' | epsilon 
 Similar steps: remove recursion, inline
*/
void term()
{
	int t;
	factor();
	while(1)
		switch(lookahead) {
		case '*': case '/' : case DIV: case MOD:
			t=lookahead;
			match(lookahead); factor(); emit (t, NONE);
			continue;
		default:
			return;
		}
}

/*
 F -> ( E ) | ID | NUM
*/
void factor()
{
		switch(lookahead) {
			case '(':
				match('('); expr(); match(')'); break;
			case NUM:
				emit(NUM, tokenval); match(NUM); break;
			case identifier:
				emit(identifier, tokenval); match(identifier); break;
			default:
				error("syntax error");
				error_count++;
				return;
	}
}

void match(t)
	int t;
{
	if (lookahead == t){
		lookahead = yylex();
		
	}
	else {
		printf("%d\n", t);
		error("Error: Syntax error - unexpected/unmatched token");
		error_count++;
		return;
	}
}



// MY EDITS - JACOB PAWLAK



void parse_program(){

	parse_start();
	parse_lines();
	parse_endprog();

}

void parse_start(){

	if (lookahead == NUM){
		parse_label();
		match(BEGN);
	}
	else{
		error("Error: Syntax requires a label before the first line");
		error_count++;
		return;
	}

}

void parse_endprog(){

	if(lookahead == END){
		match(END);
		match('.');		
	}
	else if(lookahead == DONE){
		printf("\n");
	}
	else{
		printf("the troublemite is here: %d \n", lookahead);
		error("Error: Syntax requires the last line of the program look like '(label) END.'");
		error_count++;
		return;
	}

}

void parse_lines(){

	parse_line();
	parse_linestail();

}

void parse_linestail(){

	if(lookahead == NUM){
		parse_line();
		parse_linestail();
		
	}
	else if (lookahead == DONE){
		parse_endprog();
		return;
	}
	else{
		error("Error: Syntax requires a line to be started with a label, followed by at least one statement");
		error_count++;
		return;
	}

}

void parse_line(){

	if(lookahead == NUM){
		parse_label();
		parse_statement();
	}
	else{
		error("Error: Syntax requires a line to be started with a label, followed by at least one statement*");
		error_count++;
		return;
	}
}

void parse_statement(){
	
	if (lookahead == identifier){
		parse_assignment();
		parse_goto();
		match(';');
	}
	else if(lookahead == IF){
		parse_ifstatement();
		match(';');
	}
	else if (lookahead == NUL){
		match(NUL);
		match(';');
		parse_goto();
		match(';');
	}
	else if(lookahead == PRINT){
		parse_print();
		match(';');
		parse_goto();
		match(';');
	}
	else if(lookahead == END){
		parse_endprog();
	}
	else{
		error("Error: Unexpected token before statement.");
		error_count++;
		return;
	}

}

void parse_assignment(){

	if (lookahead == identifier){
		match(identifier);
		match('=');
		expr();
		match(';');
	}
	else{
		error("Error: Unexpected token before assignment.");
		error_count++;
		return;
	}
}


void parse_label(){

	if(lookahead == NUM){
		match(NUM);
		
	}
	else{
		error("Error: Syntax requires the line start with an integer value");
		error_count++;
		return;
	}

}

void parse_print(){

	if(lookahead == PRINT){
		match(PRINT);
	}
	else{
		error("Error: Syntax requires that your print statement starts with 'PRINT' and ends with a string or identifier");
		error_count++;
		return;
	}

	if(lookahead == STRING){
		match(STRING);
	}
	else if(lookahead == identifier){
		match(identifier);
		if(lookahead == '='){
			expr();
		}
		else if(lookahead == ';'){
			match(';');
		}
	}
	else if(lookahead == NUM){
		match(NUM);
	}

}

void parse_goto(){

	if(lookahead == GOTO){
		match(GOTO);
		parse_label();
		//match(';');
	}
	else{
		error("Error: Syntax requires that your goto statement starts with 'GOTO' and ends with a valid line number");
		error_count++;
		return;
	}

}

void parse_ifstatement(){

	if(lookahead == IF){
		match(IF);
		
	}
	else{
		error("Error: Syntax requires that your if statement starts with 'IF' followed by a condition and the branching statements");
		error_count++;
		return;
	}

	parse_condition();

	if(lookahead == GOTO){
		parse_goto();
		parse_else();
		parse_goto();
	}
	else{
		error("Error: Syntax requires that your branching statements start with 'GOTO' and a line number and a ';', followed by a 'ELSE' 'GOTO' and a line number and a ';'");
		error_count++;
		return;
	}
	
}

void parse_else(){

	if(lookahead == ELSE){
		match(ELSE);
	}
	else{
		error("Error: Syntax requires that your else statement starts with 'ELSE' followed by a GOTO statement");
		error_count++;
		return;
	}
}

void parse_condition(){

	if (lookahead == '('){
		match('(');
		parse_relation();
		match(')');
		
	}
	else{
		error("Error: Syntax requires that your conditional statement starts with '(' followed by a relational statement and closed with a ')'");
		error_count++;
		return;
	}

}

void parse_relation(){

	expr();
	while(1){
		if((lookahead == 273) || (lookahead == 274) || (lookahead == 275) || (lookahead == 276) || (lookahead == '>') || (lookahead == '<')){
			match(lookahead);
			expr();
			break;
		}
		else{
			error("Error: Syntax requires that your relational statement contains a relational operator");
			error_count++;
			return;
		}
	}

}

void parse_nul(){

	if(lookahead == NUL){
		match(NUL);
	}
	else{
		error("Error: Syntax requires that your null statement starts with 'NULL' followed by a ';'");
		error_count++;
		return;
	}
}

//just for good measure, anywhere where there is an epsilon, i call this dumb little parse_eps function. it could'nt do less.
void parse_eps(){
	//printf("\n", );
	return;
}