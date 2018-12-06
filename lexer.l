%option noyywrap

%top{

	#pragma warning(disable: 4996)
}

%{
	#include "myscanner.h"
	#include <cstdlib>
	#include <iostream>
	#include "parser.hpp"
	extern int	yyparse();
	extern void	yyerror(const char *msg);
%}

commands		print|exit|push|pop|dump|assert|add|sub|mul|div|mod
single_com		print|exit|pop|dump|add|sub|mul|div|mod
com_oper		push|assert
types			int8|int16|int32|float|double
dig				[0-9]
num1			[-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2			[-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number			{num1}|{num2}
binopr 			[-+*/]
open_par 		(
close_par 		)
spaces			" "|"\t"
valid_line		{single_com}|{com_oper}{spaces}{types}{spaces}?{open_par}{spaces}?{number}{spaces}?{close_par}{spaces}?
exit_command	exit

%%
{commands}	{ 
				if (strcmp(yytext, "print"))
					return PRINT;
				else if (strcmp(yytext, "exit"))
					return EXIT;
				else if (strcmp(yytext, "push"))
					return PUSH;
				else if (strcmp(yytext, "pop"))
					return POP;
				else if (strcmp(yytext, "dump"))
					return DUMP;
				else if (strcmp(yytext, "assert"))
					return ASSERT;
				else if (strcmp(yytext, "add"))
					return ADD;
				else if (strcmp(yytext, "sub"))
					return SUB;
				else if (strcmp(yytext, "mul"))
					return MUL;
				else if (strcmp(yytext, "div"))
					return DIV;
				else if (strcmp(yytext, "mod"))
					return MOD;
			}
{types}		{
				if (strcmp(yytext, "int8"))
					return INT8;
				else if (strcmp(yytext, "int16"))
					return INT16;
				else if (strcmp(yytext, "int32"))
					return INT32;
				else if (strcmp(yytext, "float"))
					return FLT;
				else
					return DBL;
			}
{number}	{ // how do i know the type?
				if (strcmp(yytext, "int8"))
				{	
					yylval.i8 = (char)atoi(yytext);
					std::cout << "Found int8: " << yylval.i8 << std::endl;
					return LITERAL_I8;
				}
				else if (strcmp(yytext, "int16"))
				{	
					yylval.i16 = (short int)atoi(yytext);
					std::cout << "Found int16: " << yylval.i16 << std::endl;
					return LITERAL_I16;
				}
				else if (strcmp(yytext, "int32"))
				{	
					yylval.i32 = (int)atoi(yytext);
					std::cout << "Found int32: " << yylval.i32 << std::endl;
					return LITERAL_I32;
				}
				else if (strcmp(yytext, "float"))
				{	
					yylval.flt = (float)atof(yytext);
					std::cout << "Found flt: " << yylval.flt << std::endl;
					return LITERAL_FLT;
				}
				else
				{	
					yylval.flt = atof(yytext);
					std::cout << "Found dbl: " << yylval.dbl << std::endl;
					return LITERAL_DBL;
				}
}

{binopr}		{ return yytext[0]; }
[ \t\n]		;
.				{ECHO; yyerror("unexpected character");}

