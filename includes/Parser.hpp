#ifndef PARSER_HPP
# define PARSER_HPP
# include "Lexer.hpp"
# include "VirtualMachine.hpp"

class Parser
{
	Parser();
public:
	~Parser();
	static void	parse_token(s_tok token, VirtualMachine & vm);
};

#endif
