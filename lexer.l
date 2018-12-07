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
inum			[-+]?{dig}+\.?([eE][-+]?{dig}+)?
dnum			[-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number			{inum}|{dnum}
binopr 			[-+*/]
open_par 		(
close_par 		)
spaces			" "|"\t"
valid_line		{single_com}|{com_oper}{spaces}{types}{spaces}?{open_par}{spaces}?{number}{spaces}?{close_par}{spaces}?
exit_command	exit

%%
{commands}	{ 
				if (strcmp(yytext, "print"))
					yylval.command = PRINT;
				else if (strcmp(yytext, "exit"))
					yylval.command = EXIT;
				else if (strcmp(yytext, "push"))
					yylval.command = PUSH;
				else if (strcmp(yytext, "pop"))
					yylval.command = POP;
				else if (strcmp(yytext, "dump"))
					yylval.command = DUMP;
				else if (strcmp(yytext, "assert"))
					yylval.command = ASSERT;
				else if (strcmp(yytext, "add"))
					yylval.command = ADD;
				else if (strcmp(yytext, "sub"))
					yylval.command = SUB;
				else if (strcmp(yytext, "mul"))
					yylval.command = MUL;
				else if (strcmp(yytext, "div"))
					yylval.command = DIV;
				else if (strcmp(yytext, "mod"))
					yylval.command = MOD;
				return yylval.command;
			}
{types}		{
				if (strcmp(yytext, "int8"))
					yylval.type = INT8;
				else if (strcmp(yytext, "int16"))
					yylval.type = INT16;
				else if (strcmp(yytext, "int32"))
					yylval.type = INT32;
				else if (strcmp(yytext, "float"))
					yylval.type = FLT;
				else
					yylval.type = DBL;
			}
{number}	{
				if (yylval.type == INT8)
				{	
					yylval.i8 = (char)atoi(yytext);
					std::cout << "Found int8: " << yylval.i8 << std::endl;
					return yylval.i8;
				}
				else if (yylval.type == INT16)
				{	
					yylval.i16 = (short int)atoi(yytext);
					std::cout << "Found int16: " << yylval.i16 << std::endl;
					return yylval.i16;
				}
				else if (yylval.type == INT32)
				{	
					yylval.i32 = (int)atoi(yytext);
					std::cout << "Found int32: " << yylval.i32 << std::endl;
					return yylval.i32;
				}
				else if (yylval.type == FLT)
				{	
					yylval.flt = (float)atof(yytext);
					std::cout << "Found flt: " << yylval.flt << std::endl;
					return yylval.flt;
				}
				else
				{	
					yylval.flt = atof(yytext);
					std::cout << "Found dbl: " << yylval.dbl << std::endl;
					return yylval.dbl;
				}
}

{binopr}		{ return yytext[0]; }
[ \t\n]		;
.				{ECHO; yyerror("unexpected character");}

