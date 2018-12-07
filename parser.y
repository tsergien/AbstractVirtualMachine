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
	char		i8;
	short int	i16;
	int			i32;
	float		flt;
	double		dbl;
	int			command;
	int			type;
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
program: 
			: commands				{;}
			| exit_command 			{exit(EXIT_SUCCESS);}
			| print 				{printf("Printing \n");}
			| line assignment 		{;}
			| line print exp 	{printf("Printing %d\n", $3);}
			| line exit_command 	{exit(EXIT_SUCCESS);}
        ;

assignment : identifier '=' exp  { updateSymbolVal($1,$3); }
			;
exp    	: term                  {$$ = $1;}
       	| exp '+' term          {$$ = $1 + $3;}
       	| exp '-' term          {$$ = $1 - $3;}
       	;
term   	: number                {$$ = $1;}
		| identifier			{$$ = symbolVal($1);} 
        ;

%%

void yyerror(char const *msg) { std::cout << "Syntax error: " << msg << std::endl; }
