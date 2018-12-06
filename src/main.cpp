#include "../parser.hpp"
#include <iostream>

extern "C" int yyparse (void);
extern  int yylex();
extern FILE * yyin;

int main(int ac, char **av)
{
	(void)av;
	std::cout << ac << "\n";
	for (int i = 1; i < ac; i++)
	{
		FILE *myfile = fopen(av[i], "r");
		if (!myfile)
		{
			std::cerr << "I can't open " << av[i] << " file! " << std::endl;
			return -1;
		}
		// set lex to read from it instead of defaulting to STDIN:
		yyin = myfile;
	}
	
	
	while (yylex());
	
	// return yyparse();
}