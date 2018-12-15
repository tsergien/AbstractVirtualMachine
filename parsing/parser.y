%defines

%{
	#include <iostream>
	#include "../includes/VirtualMachine.hpp"
	#include "../includes/OperandCreator.hpp"

	int t;
	extern int yylex();
	extern "C" int yyparse (void);
	extern void yyerror(char const *msg);

	struct s_vm
	{
		VirtualMachine vm;
		std::string	str_num; 
	};
	s_vm	svm;
%}

%union
{
	eOperandType		etype;
	char *	str;
}

%token 			PRINT
%token 			POP
%token 			DUMP
%token 			ADD
%token 			SUB
%token 			MUL
%token 			DIV
%token 			MOD
%token 			PUSH
%token 			ASSERT
%type  <etype>	TYPE
%token <str>	INUMBER
%token <str>	DNUMBER
%type  <str>	number

%token			END
%token			COMMENT

%locations

%%

input	: END 
		| list END 	{std::cout << "program started\n";}
		;

list	: comm
		| list comm
		;

comm	: PRINT	{svm.vm.print();}
		| END	{exit(EXIT_SUCCESS);}
		| POP	{svm.vm.pop();}
		| DUMP	{svm.vm.dump();}
		| ADD	{svm.vm.add();}
		| SUB	{svm.vm.sub();}
		| MUL	{svm.vm.mul();}
		| DIV	{svm.vm.div();}
		| MOD	{svm.vm.mod();}
		| PUSH TYPE '(' number ')'	{svm.vm.push(OperandCreator::get_instance()->createOperand($2, (std::string)$4));}
		| ASSERT TYPE '(' number ')'	{svm.vm.assert_(OperandCreator::get_instance()->createOperand($2, (std::string)$4));}
		;

TYPE:		{ t = (int)$$; };

number:		DNUMBER		{  }; 
			| INUMBER	{  };

%%

void yyerror(char const *msg) { std::cerr << "Syntax error: " << msg << std::endl; }

// void ad_error( const location_type &l, const std::string &err_message ) { std::cerr << "Error: " << err_message << " at " << l << std::endl; }
