%skeleton "lalr1.cc"
%defines

%{
	#include <iostream>
	#include <cmath>
	#include "includes/VirtualMachine.hpp"
	#include "includes/OperatorCreator.hpp"

	extern int yylex();

	extern "C" int yyparse (void);
	extern void yyerror(char const *msg);
%}

%start input

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


%type <int>	type
%type<dbl>	line
%type<std::string>	number

%%

input:	/* empty */
		| input line
		;

line:	PRINT	{vm.print();}
		| ws EXIT	{exit(EXIT_SUCCESS);}
		| ws POP	{vm.pop();}
		| ws DUMP	{vm.dump();}
		| ws ADD	{vm.add();}
		| ws SUB	{vm.sub();}
		| ws MUL	{vm.mul();}
		| ws DIV	{vm.div();}
		| ws MOD	{vm.mod();}
		| ws PUSH ws type ws '(' ws number ws ')'	{vm.push(Operandreator::get_instance()->createOperand(type, number));}
		| ws ASSERT ws type ws '(' ws number ws ')'	{vm.assert(Operandreator::get_instance()->createOperand(type, number));}
		;

type:	{ $$ = ltypes; }
		;

number:		L_DBL		{ $$ = $1; };

ws:			{};

%%

void yyerror(char const *msg) { std::cout << "Syntax error: " << msg << std::endl; }
