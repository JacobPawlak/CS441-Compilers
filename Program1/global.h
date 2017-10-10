//Jacob Pawlak
//CS441G Compilers
//October 7th, 2017

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'

#define NUM 256
#define DIV 257
#define MOD 258
#define identifier  259
#define DONE 260
#define IF 261
#define ELSE 262
#define END 263
#define BEGN 264
#define GOTO 265
#define NUL 266
#define PRINT 267
#define READ 268
#define num 270
#define STRING 271
#define look 269
#define LESSEQUAL 273
#define GREATEREQUAL 274
#define EQUALS 275
#define NOTEQUAL 276

#define SYMMAX 100   /* size of symtable */

char yystring[1000];
int yylex();
char stringval[1000];

int tokenval;    /* value of token atribute  */
int lineno;

typedef struct entry entry;
struct entry { /* form of symbol table entry */
  char *lexptr;
  int token;
  int count;
  entry *next;
  char str[];
};
entry *symtable[SYMMAX]; /* symbol table */
entry *tokensym; /* use in place of tokenval for identifiers */

void error(char *m);
entry* lookup(char s[], int current_token);
void parse();
void expre();
void match(int t);


void parse_print();
void parse_lines();
void parse_statement();
void parse_assignment();
void parse_program();
void parse_start();
void parse_endprog();
void parse_line();
void parse_linestail();
void parse_label();
void parse_goto();
void parse_ifstatement();
void parse_else();
void parse_condition();
void print_symbol_table();
void parse_relation();
void parse_nul();
void parse_eps();

void expr();
void term();
void factor();


int lexan();
void emit(int t, int tval);
void init();
void exit(int n);
int main();

