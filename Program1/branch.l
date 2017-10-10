/*
Jacob Pawlak
CS441G Compilers
October 7th, 2017
pa1
*/

%option input
%option unput
%option noyywrap

%{
#include "global.h"
%}

delim           [\t ]
ws              {delim}+
digit           [0-9]
num             {digit}+
alpha           [_a-zA-Z]
identifier      {alpha}({alpha}|{digit})*
string			[\"][a-zA-Z0-9 ]*[\"]
quote			[\"]
if				"IF"
else			"ELSE"
begn			"BEGIN"
end				"END"
equals			"=="
lessequal		"<="
greaterequal	">="
notequal		"!="
goto			"GOTO"
nul				"NULL"
print			"PRINT"
read			"READ"


%%

{ws}            {/* skip! */}

{num}			{
					tokenval = atoi(yytext);
					return NUM;
				}

{string}		{strcpy(stringval,yytext);return STRING;}

{if}			{return IF;}

{else}			{return ELSE;}

{begn}			{return BEGN;}

{end}			{return END;}

{nul}			{return NUL;}

{goto}			{return GOTO;}

{read}			{return READ;}

{print}			{return PRINT;}



{identifier}	{
					if (strlen(yytext) >= BSIZE) {
						error("compiler error, the name of the identifier is too long");
					}
					tokensym = lookup(yytext, identifier);
					return (int)tokensym->token;
				}

"*"				{return '*';}
"/"				{return '/';}
"+"				{return '+';}
"-"				{return '-';}
"%"				{return MOD;}

"("				{return '(';}
")"				{return ')';}

"\n"			{lineno++; /*printf("\n");*/}


"<"				{return '<';}
">"				{return '>';}
{lessequal} 	{return LESSEQUAL;}
{greaterequal}	{return GREATEREQUAL;}
{equals}		{return EQUALS;}
{notequal}		{return NOTEQUAL;}

";"				{return ';';}
"."				{return '.';}
"="				{return '=';}

{quote}			{return '\"';}

<<EOF>>			{return DONE;}
.				{error("That was not a recognized character in this language");}
