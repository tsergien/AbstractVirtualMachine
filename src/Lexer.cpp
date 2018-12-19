#include "../includes/Lexer.hpp"
#include <regex>

Lexer::Lexer(): token(new s_tok){}
Lexer::~Lexer(){if (token )delete token;}
Lexer::Lexer(Lexer const & other){*this = other;}
Lexer const & Lexer::operator=(Lexer const & other)
{
	if (token) delete token;
	token = new s_tok(other.token->command, token->type,token->value, token->comment);
	return *this;
}

bool Lexer::set_token(std::string s)
{
    std::smatch res;
    std::regex  line("(dump|add|sub|mul|div|mod|exit|print|pop)"
                        "|"
						"(push|assert)(\\s+)(int8|int16|int32|float|double)"
                        "(\\s*)(\\()(\\s*)"
                        "([-+]?[0-9]*\\.?[0-9]+)"
                        "(\\s*)(\\))(\\s*)"
                        );
	std::regex	command("(assert|push|dump|add|sub|mul|div|mod|exit|print|pop)");
	std::regex	type("(int8|int16|int32|float|double)");
	std::regex	val("(\\()(\\s*)([-+]?[0-9]*\\.?[0-9]+)");
	std::regex	comment("(^;)");    

	try
	{
		token->command = "";
		token->comment = "";
		token->type = "";
		token->value = "";
		if (std::regex_search(s, res, comment)) {token->comment = s; return 1;}
		else if (std::regex_match(s, res, line))
		{
			if (std::regex_search(s, res, command))
				token->command = res[1].str();
			if (std::regex_search(s, res, type))
				token->type = res[1].str();
			if (std::regex_search(s, res, val))
				token->value = (res[2] == "(") ? res[2].str() : res[3].str();
			return 1;
		}
		else throw Lexer::InstrUnknown();
	}
	catch(std::exception & e) {std::cout << e.what();exit(0);}
	return 0;
}

s_tok * Lexer::get_token() const
{
	return token;
}

s_tok & Lexer::get_clone() const
{
	s_tok  *res = new s_tok(token->command, token->type, token->value, token->comment);
	return (*res);
}
