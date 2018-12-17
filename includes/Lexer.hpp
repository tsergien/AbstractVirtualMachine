#ifndef LEXER_HPP
# define LEXER_HPP
# include <iostream>
# include <vector>

struct	s_tok
{
	std::string command;
	std::string type;
	double 		value;
};

class Lexer
{
	Lexer();
	~Lexer();
	Lexer(Lexer const & other);
	Lexer const & operator=(Lexer const & other);

	std::vector<s_tok *> get_tokens(std::istream & is);

private:
	std::vector<s_tok *> tokens;
};

#endif