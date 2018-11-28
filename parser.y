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
	double dbl;
};

%token<dbl> LITERAL_DBL

%type<dbl> expr
%type<dbl> term

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
void yyerror(char const *msg)
{
	std::cout << "Syntax error: " << msg << std::endl;
}
