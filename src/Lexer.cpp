#include "../includes/Lexer.hpp"
#include <regex>

Lexer::Lexer(): token(new s_tok){}
Lexer::~Lexer(){if (token )delete token;}
Lexer::Lexer(Lexer const & other){*this = other;}
Lexer const & Lexer::operator=(Lexer const & other)
{
	if (token) delete token;
	token = new s_tok;
	token->command = other.token->command;
	token->command = other.token->type;
	token->value = other.token->value;
	return *this;
}

bool Lexer::set_token(std::string s)
{
    std::smatch result;
    std::regex  line("(dump|add|sub|mul|div|mod|exit|print|pop)"
                        "|"
						"(push|assert)(\\s+)(int8|int16|int32|float|double)"
                        "(\\()(\\s*)"
                        "([-+]?[1-9][0-9]*\\.?[0-9]+)"
                        "(\\s*)(\\))"
                        );
	std::regex	command("(assert|push|add|sub|mul|div|mod|exit|print|pop)");
	std::regex	type("(int8|int16|int32|float|double)");
	std::regex	val("(\\()([-+]?[1-9][0-9]*\\.?[0-9]+)");
	std::regex	ex("(^;;)");
	std::regex	comment("(^;)");    

	try
	{
		if (std::regex_search(s, result, ex))
			token->command = "exit";
		else if (std::regex_search(s, result, comment))
			std::cout << "comment: " << s << std::endl;
		else if (std::regex_match(s, result, line))
		{
			token->type = "";
			token->value = "";
			if (std::regex_search(s, result, command))
				token->command = result[1].str();
			if (std::regex_search(s, result, type))
				token->type = result[1].str();
			if (std::regex_search(s, result, val))
				token->value = result[2].str();
			std::cout << "tok->c="<<token->command<<", tok->t="<<token->type<<", tok->val="<<token->value<<std::endl;
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

s_tok Lexer::get_clone() const
{
	s_tok res;
	res.command = token->command;
	res.type = token->type;
	res.value = token->value;
	return res;
}

// void Lexer::read_tokens(std::istream & is)
// {
// 	std::string s;
//     std::smatch result;
//     std::regex  command("(add|sub|mul|div|mod|exit|print|pop)"
//                         "|"
// 						"(push|assert)(\\s)(int8|int16|int32|float|double)"
//                         "(\\()"
//                         "(([-+]?[1-9][0-9]*\\.?[0-9]+[eE][+-]?[0-9]+)"
//                         "|"
//                         "([-+]?[1-9][0-9]*\\.?[0-9]+))"
//                         "(\\))"
//                         );

//     while (std::getline(is, s, '\n'))
//     {
//         if (std::regex_match(s, result, command))
// 		{
// 			std::regex_match(s, result, command);
// 			tokens.push_back(create_token(result));
// 		}
// 	}
// }