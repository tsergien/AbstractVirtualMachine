#ifndef LEXER_HPP
# define LEXER_HPP
# include <iostream>
# include <vector>

struct	s_tok
{
	std::string command;
	std::string type;
	std::string value;
	std::string comment;
};

class Lexer
{
public:
	class LexicalError : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mLexical error \033[0m\n";
		}
	};
	class InstrUnknown : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: unknown instruction \033[0m\n";
		}
	};
	class NoExitInstr : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: no exit instruction \033[0m\n";
		}
	};
	Lexer();
	~Lexer();
	Lexer(Lexer const & other);
	Lexer const & operator=(Lexer const & other);

	void	read_tokens(std::istream & is, std::vector<s_tok> & tokens);
	s_tok	set_token(std::string s);
};

#endif