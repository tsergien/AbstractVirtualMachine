%option noyywrap

%top{

	#pragma warning(disable: 4996)
}

%{
	#include <cstdlib>
	#include "parser.hpp"

	extern int yyparse();
%}

commands [push|pop|dump|assert|add|sub|mul|div|mod|print|exit]
types [int8|int16|int32|float|double]
digits [+-]?[0-9]+
binopr [-+*/]
parenthesis [()]

%%
{digits}	{
	
				yylval.dbl = atof(yytext);
				return LITERAL_DBL;
			}

{binopr}	{ return yytext[0]; }
\n			{ return '\n'; }
.

