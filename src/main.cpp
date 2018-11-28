#include "../parser.hpp"
//#pragma warning(disable: 4996)
extern "C" int yyparse (void);

int main(int ac, char **av)
{
	ac = 0;
	(void)av;
	return yyparse();
}