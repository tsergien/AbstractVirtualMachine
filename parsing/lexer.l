%option noyywrap

%{
	#include <cstdlib>
	#include <iostream>
	#include "parser.hpp"
	#include "../includes/VirtualMachine.hpp"
	#include "../includes/OperandCreator.hpp"
	extern int	yyparse();
	extern void	yyerror(const char *msg);
%}

l_types			int8|int16|int32|float|double
dig				[0-9]
inum			[-+]?{dig}+
dnum			[-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number			{inum}|{dnum}
ws				[ \t\r\n]
value			[type][ws][(][l_types][)]

%option debug
%option nodefault
%option yyclass="VirtualMachine"
%option c++

%%
print			{return token::PRINT;}
exit			{return token::END;}
pop				{return token::POP;}
DUMP			{return token::DUMP;}
add				{return token::ADD;}
sub				{return token::SUB;}
mul				{return token::MUL;}
div				{return token::DIV;}
mod				{return token::MOD;}
push			{return token::PUSH;}
assert			{return token::ASSERT;}

int8			{ yylval.i = 0; return TYPE}
int16			{ yylval.i = 1; return TYPE}
int32			{ yylval.i = 2; return TYPE}
float			{ yylval.i = 3; return TYPE}
double			{ yylval.i = 4; return TYPE}

{inum}			{
					std::cout << "yylval: " << yylval << std::endl;
					// yylval->build< std::string >( yytext );
               		return( token::INUMBER );
				}

{dnum}			{
					std::cout << "yylval: " << yylval << std::endl;
					// yylval->build< std::string >( yytext );
               		return( token::DNUMBER );
				}

ws				;
;;				{ return token::END; }
;				{ return token::COMMENT; }
.				{ECHO; yyerror("unexpected character");}
