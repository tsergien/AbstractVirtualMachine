%defines

%{
	#pragma warning(disable: 4996)

	#include <iostream>
	#include <cmath>

	extern int yylex();

	extern "C" int yyparse (void);
	extern void yyerror(char const *msg);
%}

%union
{
	double		dbl;
	char		i8;
	short int	i16;
	int			i32;
	float		flt;
};

%token <i8>		LITERAL_I8
%token <i16>	LITERAL_I16
%token <i32>	LITERAL_I32
%token <flt>	LITERAL_FLT
%token <dbl>	LITERAL_DBL
%token			exit_command

%type <dbl>		expr
%type <dbl>		term

%start program
%%
program: /* empty */
	| program expr '\n' {std::cout << $2 << std::endl;}
	;

expr: term	{ $$ = $1; }
	| expr '+' term { $$ = $1 + $3 ; } // $1 is semantic value of expr
	| expr '-' term { $$ = $1 - $3 ; } // $3 is semantic value of term
	;

term: LITERAL_DBL { $$ = $1; }
	| term '*' LITERAL_DBL { $$ = $1 * $3 ; }
	| term '/' LITERAL_DBL { $$ = $1 / $3 ; }
	;

%%

void yyerror(char const *msg) { std::cout << "Syntax error: " << msg << std::endl; }
