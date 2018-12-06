%option noyywrap

%top{

	#pragma warning(disable: 4996)
}

%{
	#include <cstdlib>
	#include <iostream>
	#include "parser.hpp"

	extern int yyparse();
%}

commands print|exit|push|pop|dump|assert|add|sub|mul|div|mod
types int8|int16|int32|float|double
dig		[0-9]
num1    [-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2    [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number  {num1}|{num2}
binopr [-+*/]
parenthesis [()]
exit_command	exit

%%
{number}	{
				std::cout << "Found number: " << yytext << std::endl;
				yylval.dbl = atof(yytext);
				return LITERAL_DBL;
			}

{binopr}	{ return yytext[0]; }
{types}		{ return yytext; }
{commands}		{ std::cout << "Found command: " << yytext << std::endl; }
\n			{ return '\n'; }
.

