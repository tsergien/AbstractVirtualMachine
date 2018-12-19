#ifndef PARSER_HPP
# define PARSER_HPP
# include "Lexer.hpp"
# include "VirtualMachine.hpp"
# include <map>

class Parser
{


	Parser();
	Parser(Parser const & other) = delete;
	Parser const & operator=(Parser const & other) = delete;
public:
	~Parser();
	static void	parse_token(s_tok & token, VirtualMachine & vm);
};

#endif
