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
	class WrongType : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mLexical error: not existing type \033[0m\n";
		}
	};
	class WrongValue : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mLexical error: value format is wrong. \033[0m\n"
			"Expected: int_type([-]?[0..9]+) | float_point([-]?[0..9]+.[0..9]+) \n";
		}
	};
	Lexer();
	~Lexer();
	Lexer(Lexer const & other);
	Lexer const & operator=(Lexer const & other);

	void	read_tokens(std::istream & is, std::vector<s_tok> & tokens);
	s_tok	set_token(std::string s);
	int		lineno() const;
};

#endif