#include "../includes/Type.hpp"
#include "../includes/VirtualMachine.hpp"
#include "../includes/Parser.hpp"
#include <regex>
#include <string>
#include <errno.h>
#include <fstream>
// coommands after exit in the standart input: shpuld they be ignored?
// Line 1 : Error : pop on empty stack
static void		exec_input(std::istream & is)
{
	Lexer lex;
	VirtualMachine vm;
	std::vector<s_tok> tokens;

	lex.read_tokens(is, tokens);
	for (unsigned j = 0; j < tokens.size(); j++)
		Parser::parse_token(tokens[j], vm);
}

int				main(int ac, char **av)
{
	if (ac == 1)
		exec_input(std::cin);		
	for (int i = 1;  i < ac; i++)
	{
		std::filebuf fb;
		if (fb.open(av[i] ,std::ios::in))
 		{
    		std::istream is(&fb);
			exec_input(is);
    		fb.close();
  		}
		if (errno)
			std::cerr << av[i] << ": " << strerror(errno) << std::endl; 
	}
    return 0;
}
