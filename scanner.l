%{
	#include <iostream>
	// #include <string.h>
	// "+" 			{ 	return PLUS_OP; }
	#include "parser.tab.h"
	extern "C" void yyerror(char *);

%}
%option yylineno

digit [0-9]
double  \.{digit}+|{digit}+\.{digit}+?
letter [a-zA-Z_]
name {letter}({letter}|{digit})*
whitespace [ \n\t\r\f]+
metas [\[\]\:\?,;\(\)\{\}]
ops [\-\+\*\/]
slc  \/\/.*



%%
{whitespace} ;
{slc} ;
"int" 			{ 	return INTEGER; }
"for"			{	return FOR; 	}
{digit}+    	{ 	yylval.integer = atoi(yytext);				return INTEGER_NUMBER;	}
{name} 			{  	yylval.stringer = new std::string(yytext);  return NAME;	}
"=" 			{ 	return ASSIGN_OP; }
">="			{ 	return GTE; }
"<="			{ 	return LTE; }
"!="			{ 	return NEQ; }
"=="			{ 	return EQ; }
">"				{ 	return GT; }
"<"				{ 	return LT; }
"!"				{ 	return NOT; }
{ops} 			{ 	return yytext[0];}
{metas}			{  	return yytext[0];}
. 				{   fprintf(stderr,"Scanner Error : in line %d, Unknown character: %s\n",yylineno,yytext); exit(0);}

