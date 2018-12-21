#ifndef PARSER_HPP
# define PARSER_HPP
# include "VirtualMachine.hpp"
# include "Lexer.hpp"

class Parser
{
	Parser();
	Parser(Parser const & other) = delete;
	Parser const & operator=(Parser const & other) = delete;
public:
	~Parser();
	static	int	lineno();
	static void	parse_token(s_tok & token, VirtualMachine & vm);
	static void	parse(std::vector<s_tok> & tokens, VirtualMachine & vm);
};

#endif
