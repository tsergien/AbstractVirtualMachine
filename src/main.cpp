#include "../parser.hpp"
#include <iostream>
#include "../myscanner.h"


extern "C" int yyparse (void);
extern  int yylex();
extern FILE * yyin;
extern int	yylineno;
extern char *yytext;

int		start_program()
{
	//while (yylex());


	return yyparse();
}

int 	main(int ac, char **av)
{
	if (ac == 1)
		start_program();
	for (int i = 1; i < ac; i++)
	{
		FILE *myfile = fopen(av[i], "r");
		if (!myfile)
		{
			std::cerr << "Can't open " << av[i] << " file! " << std::endl;
			return -1;
		}
		yyin = myfile;
		start_program();
	}
	return (0);
}