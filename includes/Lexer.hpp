#ifndef LEXER_HPP
# define LEXER_HPP
# include <iostream>
# include <vector>

struct	s_tok
{
	std::string command;
	std::string type;
	std::string value;
	std::string comment = "";
	s_tok(std::string c="", std::string t="", std::string v="", std::string com="") 
	: command(c), type(t), value(v), comment(com) {}
};

class Lexer
{
public:
	class LexicalError : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mLexical error: \033[0m\n";
		}
	};
	class InstrUnknown : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: unknown instruction \033[0m\n";
		}
	};
	Lexer();
	~Lexer();
	Lexer(Lexer const & other);
	Lexer const & operator=(Lexer const & other);

	bool set_token(std::string s);
	s_tok * get_token() const;
	s_tok & get_clone() const;
private:
	bool	is_exit;
	s_tok	*token;
};

#endif