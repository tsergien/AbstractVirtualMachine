%option noyywrap

%{
	#include <cstdlib>
	#include <iostream>
	#include "parser.hpp"
	extern int	yyparse();
	extern void	yyerror(const char *msg);
%}

dig				[0-9]
inum			[-+]?{dig}+
dnum			[-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number			{inum}|{dnum}
ws				[ \t\r\n]

%%
print			{return PRINT;}
exit			{return EXIT;}
pop				{return POP;}
DUMP			{return DUMP;}
add				{return ADD;}
sub				{return SUB;}
mul				{return MUL;}
div				{return DIV;}
mod				{return MOD;}
push			{return PUSH;}
assert			{return ASSERT;}

int8			{return INT8;}
int16			{return INT16;}
int32			{return INT32;}
flt				{return FLT;}
dbl				{return DBL;}

{number}	{
				std::cout << "yylval: " << yylval << std::endl;
				if (yylval == INT8)
				{
					yylval.i8 = (char)atoi(yytext);
					std::cout << "Found int8: " << yylval.i8 << std::endl;
					return L_I8;
				}
				else if (yylval == INT16)
				{
					yylval.i16 = (short int)atoi(yytext);
					std::cout << "Found int16: " << yylval.i16 << std::endl;
					return L_I16;
				}
				else if (yylval == INT32)
				{
					yylval.i32 = (int)atoi(yytext);
					std::cout << "Found int32: " << yylval.i32 << std::endl;
					return L_I32;
				}
				else if (yylval == FLT)
				{
					yylval.flt = (float)atof(yytext);
					std::cout << "Found flt: " << yylval.flt << std::endl;
					return L_FLT;
				}
				else
				{
					yylval.flt = atof(yytext);
					std::cout << "Found dbl: " << yylval.dbl << std::endl;
					return L_DBL;
				}
			}
ws				;
.				{ECHO; yyerror("unexpected character");}

