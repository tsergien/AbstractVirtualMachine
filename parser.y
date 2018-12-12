%defines

%{
	#pragma warning(disable: 4996)

	#include <iostream>
	#include <cmath>
	#include "includes/VirtualMachine.hpp"

	extern int yylex();

	extern "C" int yyparse (void);
	extern void yyerror(char const *msg);
%}

%start input
%union
{
	char		i8;
	short int	i16;
	int			i32;
	float		flt;
	double		dbl;
};

%token <VirtualMachine>		vm
%token <i8>		L_I8
%token <i16>	L_I16
%token <i32>	L_I32
%token <flt>	L_FLT
%token <dbl>	L_DBL

%token 			INT8
%token 			INT16
%token 			INT32
%token 			FLOAT
%token 			DOUBLE

%token 			PRINT
%token 			EXIT
%token 			POP
%token 			DUMP
%token 			ADD
%token 			SUB
%token 			MUL
%token 			DIV
%token 			MOD
%token 			PUSH
%token 			ASSERT 			

%token <int>	L_COMMAND
%token <int>	L_TYPE

%type<dbl>	line
%type<i32>	oper_com
%type<i32>	single_com
%type<i32>	type
%type<i32>	number

%%

input:	/* empty */
		| input line
		;

line:	PRINT	{vm.print();}
		| ws EXIT ws	{exit(EXIT_SUCCESS);}
		| ws POP ws		{vm.pop();}
		| ws DUMP ws	{vm.dump();}
		| ws ADD ws		{vm.add();}
		| ws SUB ws		{vm.sub();}
		| ws MUL ws		{vm.mul();}
		| ws DIV ws		{vm.div();}
		| ws MOD ws		{vm.mod();}
		| ws PUSH  ws  type  ws  '('  ws  number  ')'  ws	{std::cout << "push  ws  type  ws  '('  ws  number  ')'  ws\n";} 
		| ws ASSERT  ws  type  ws  '('  ws  number  ')'  ws	{std::cout << "assert  ws  type  ws  '('  ws  number  ')'  ws\n";} 
		;

number:		L_DBL		{ $$ = $1; };

ws:			{};

%%

void yyerror(char const *msg) { std::cout << "Syntax error: " << msg << std::endl; }
