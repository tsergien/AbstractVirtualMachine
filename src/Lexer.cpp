#include "../includes/Lexer.hpp"
#include <regex>

Lexer::Lexer(){}
Lexer::~Lexer(){}
Lexer::Lexer(Lexer const & other){*this = other;}
Lexer const & Lexer::operator=(Lexer const & other){
	tokens = other.tokens;
	return *this;
}

s_tok		*create_token(std::smatch res)
{
	unsigned size = res.size();
	for (unsigned i = 1; i < size; i++)
	{
		if (res[i].str().empty())
			continue ;
		
	}
}

std::vector<s_tok *> Lexer::get_tokens(std::istream & is)
{
	std::string s;
    std::smatch result;
    std::regex  command("(add|sub|mul|div|mod|exit|print|pop)"
                        "|"
						"(push|assert)(\\s)(int8|int16|int32|float|double)"
                        "(\\()"
                        "(([-+]?[1-9][0-9]*\\.?[0-9]+[eE][+-]?[0-9]+)"
                        "|"
                        "([-+]?[1-9][0-9]*\\.?[0-9]+))"
                        "(\\))"
                        );

    while (std::getline(is, s, '\n'))
    {
        if (std::regex_match(s, result, command))
			tokens.push_back(create_token(result));
	}
}
    